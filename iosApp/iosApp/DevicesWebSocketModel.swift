//
//  DeviceWebSocketModel.swift
//  iosApp
//
//  Created by Valentin Werner on 01.08.25.
//
import Foundation

class DevicesWebSocketModel: ObservableObject
{
    @Published var groupedDevices: [String: [DeviceModel]] = [:]
    
    private var webSocketTask: URLSessionWebSocketTask?

    init() {
        connectWebSocket()
    }

    func connectWebSocket() {
        guard let url = URL(string: "ws://192.168.2.123:8080/homeAutomation/ws/deviceTracker") else { return }
        let session = URLSession(configuration: .default)
        webSocketTask = session.webSocketTask(with: url)
        webSocketTask?.resume()
        listen()
    }

    private func listen() {
        webSocketTask?.receive { [weak self] result in
            guard let self = self else { return }
            switch result {
            case .success(let message):
                switch message {
                case .data(let data):
                    self.processMessage(data)
                case .string(let text):
                    if let data = text.data(using: .utf8) {
                        self.processMessage(data)
                    }
                @unknown default:
                    break
                }
            case .failure(let error):
                print("WebSocket error: \(error)")
            }

            self.listen() // Keep listening
        }
    }

    private func processMessage(_ data: Data) {
        print("processing message")
        
        do {
            let devices = try JSONDecoder().decode([DeviceModel].self, from: data)
            let grouped = Dictionary(grouping: devices, by: { $0.name })

            
            Task { @MainActor in
                self.groupedDevices = grouped
            }
        } catch {
            print("Decoding error: \(error)")
        }
    }

    deinit {
        webSocketTask?.cancel(with: .goingAway, reason: nil)
    }
}
