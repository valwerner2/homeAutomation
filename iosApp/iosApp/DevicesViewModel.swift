//
//  DeviceInfoViewModel.swift
//  iosApp
//
//  Created by Valentin Werner on 31.07.25.
//
import Foundation

class DevicesViewModel: ObservableObject {
    
    @Published var groupedDevices: [String: [DeviceModel]] = [:]
    @Published var editingDeviceID: UUID? = nil
    @Published var editedName: String = ""
    @Published var responseChangeName: String?
    @Published var errorChangeName: String?
    
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
    
    private func findDevice(by id: UUID) -> DeviceModel? {
        return groupedDevices
            .flatMap { $0.value } // Flattens [[DeviceInfo]] into [DeviceInfo]
            .first { $0.id == id } // Finds the first match
    }
    
    func changeName() {
        var ip: String = ""
            if let id = editingDeviceID, let device = findDevice(by: id) {
                print("Device found.")
                ip = device.ip
            } else {
                print("Device not found.")
                errorChangeName = "Device not found."
                return
            }
            guard let url = URL(string: "http://\(ip)/deviceBroadcaster/name") else {
                errorChangeName = "Invalid IP address."
                return
            }

            let body: [String: String] = ["name": editedName]
            guard let jsonData = try? JSONSerialization.data(withJSONObject: body) else {
                errorChangeName = "Failed to encode JSON."
                return
            }

            var request = URLRequest(url: url)
            request.httpMethod = "PUT"
            request.setValue("application/json", forHTTPHeaderField: "Content-Type")
            request.httpBody = jsonData

            URLSession.shared.dataTask(with: request) { data, response, error in
                DispatchQueue.main.async {
                    if let error = error {
                        self.errorChangeName = "Request error: \(error.localizedDescription)"
                        return
                    }

                    guard let httpResponse = response as? HTTPURLResponse else {
                        self.errorChangeName = "Invalid response"
                        return
                    }

                    if httpResponse.statusCode == 200 {
                        self.responseChangeName = "Success"
                    } else {
                        self.errorChangeName = "HTTP Error: \(httpResponse.statusCode)"
                    }
                }
            }.resume()
        }
}
