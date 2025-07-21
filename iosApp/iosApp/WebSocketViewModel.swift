//
//  WebSocketViewModel.swift
//  iosApp
//
//  Created by Valentin Werner on 21.07.25.
//

import Foundation

class WebSocketViewModel: ObservableObject {
    @Published var message: String = "Waiting for message..."
    
    private var webSocketTask: URLSessionWebSocketTask?
    
    init() {
        connect()
    }
    
    func connect() {
        guard let url = URL(string: "ws://192.168.2.123:8080/homeAutomation/ws/deviceTracker") else { return }
        let session = URLSession(configuration: .default)
        webSocketTask = session.webSocketTask(with: url)
        webSocketTask?.resume()
        listen()
    }
    
    private func listen() {
        webSocketTask?.receive { [weak self] result in
            switch result {
            case .success(let message):
                switch message {
                case .string(let text):
                    DispatchQueue.main.async {
                        self?.message = text
                    }
                case .data(let data):
                    print("Received binary data: \(data)")
                @unknown default:
                    print("Unknown message")
                }
                self?.listen() // Keep listening
            case .failure(let error):
                print("WebSocket error: \(error)")
            }
        }
    }
    
    deinit {
        webSocketTask?.cancel(with: .goingAway, reason: nil)
    }
}
