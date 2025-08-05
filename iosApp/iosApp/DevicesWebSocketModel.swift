//
//  DeviceWebSocketModel.swift
//  iosApp
//
//  Created by Valentin Werner on 01.08.25.
//
import Foundation
import NotificationCenter

class DevicesWebSocketModel: ObservableObject
{
    @Published var devices: [DeviceModel] = []
    @Published var isConnected: Bool = false
    
    private var reconnectDelay: TimeInterval = 5
    private var webSocketTask: URLSessionWebSocketTask?

    init() {
        connectWebSocket()
        addAppLifecycleObservers()
    }
    
    private func addAppLifecycleObservers() {
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(appDidBecomeActive),
            name: UIApplication.didBecomeActiveNotification,
            object: nil
        )	

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(appWillResignActive),
            name: UIApplication.willResignActiveNotification,
            object: nil
        )
    }
	
    @objc private func appDidBecomeActive() {
        print("App became active → reconnecting WebSocket")
        connectWebSocket()
    }

    @objc private func appWillResignActive() {
        print("App will resign active → closing WebSocket")
        webSocketTask?.cancel(with: .goingAway, reason: nil)
        webSocketTask = nil
        isConnected = false
    }
    
    func connectWebSocket() {
        guard let url = URL(string: "ws://192.168.2.123:8080/homeAutomation/ws/deviceTracker") else { return }
        let session = URLSession(configuration: .default)
        webSocketTask = session.webSocketTask(with: url)
        webSocketTask?.resume()
        DispatchQueue.main.async {
            self.isConnected = true
        }
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
                DispatchQueue.main.async{
                    self.isConnected = false
                }
                DispatchQueue.global().asyncAfter(deadline: .now() + self.reconnectDelay) {
                                        print("Attempting to reconnect...")
                                        self.connectWebSocket()
                                    }
            }
            
            if(webSocketTask != nil && self.isConnected)
            {
                self.listen() // Keep listening
            }
        }
    }

    private func processMessage(_ data: Data) {
        print("processing message")
        
        do {
            let devices = try JSONDecoder().decode([DeviceModel].self, from: data)

            
            Task { @MainActor in
                self.devices = devices
            }
        } catch {
            print("Decoding error: \(error)")
        }
    }

    deinit {
        webSocketTask?.cancel(with: .goingAway, reason: nil)
        NotificationCenter.default.removeObserver(self)
        isConnected = false
    }
}
