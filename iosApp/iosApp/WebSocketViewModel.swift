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
/*
 struct DevicesView: View {
     @StateObject private var viewModel = DevicesViewModel()
     
     @State private var editingDeviceID: UUID? = nil
     @State private var editedPurpose: String = ""
     
     let verticalSpacing: CGFloat = 16
     let verticalPadding: CGFloat = 4
     let activeColor = Color.blue
     let inactiveColor = Color.gray
     
     var body: some View {
         NavigationStack {
             List {
                 ForEach(viewModel.groupedDevices.keys.sorted(), id: \.self) { name in
                     if let devices = viewModel.groupedDevices[name] {
                         Section(
                             header: Text(name)
                                 .font(.headline)
                                 .textCase(nil)
                         ) {
                             ForEach(devices) { device in
                                 HStack {
                                     VStack(alignment: .leading, spacing: verticalSpacing) {
                                         
                                         if editingDeviceID == device.id {
                                             // Show TextField for editing purpose
                                             TextField("Edit purpose", text: $editedPurpose)
                                                 .textFieldStyle(.roundedBorder)
                                         } else {
                                             Text("Purpose: \(device.purpose)")
                                         }
                                         
                                         Text("IP: \(device.ip)")
                                         Text("MAC: \(device.mac)")
                                     }
                                     .padding(.vertical, verticalPadding)
                                     
                                     Spacer()
                                     
                                     VStack(alignment: .center, spacing: verticalSpacing) {
                                         Image(systemName: device.active ? "wifi" : "wifi.slash")
                                             .foregroundStyle(device.active ? activeColor : inactiveColor)
                                         
                                         Button(action: {
                                             print("Eye button was pressed!")
                                         }) {
                                             Image(systemName: device.active ? "eye" : "eye.slash")
                                                 .foregroundStyle(device.active ? activeColor : inactiveColor)
                                         }
                                         .buttonStyle(.plain)
                                         
                                         Button(action: {
                                             if editingDeviceID == device.id {
                                                 // Save changes and close editor
                                                 viewModel.updateDevice(deviceID: device.id, newPurpose: editedPurpose)
                                                 editingDeviceID = nil
                                             } else {
                                                 // Start editing
                                                 editedPurpose = device.purpose
                                                 editingDeviceID = device.id
                                             }
                                         }) {
                                             Image(systemName: editingDeviceID == device.id ? "checkmark" : "pencil")
                                                 .foregroundStyle(device.active ? activeColor : inactiveColor)
                                         }
                                         .buttonStyle(.plain)
                                     }
                                     .padding(.vertical, verticalPadding)
                                 }
                             }
                         }
                     }
                 }
             }
             .navigationTitle("Devices")
         }
     }
 }

 */
