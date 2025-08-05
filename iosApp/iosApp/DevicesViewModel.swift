//
//  DeviceInfoViewModel.swift
//  iosApp
//
//  Created by Valentin Werner on 31.07.25.
//
import Foundation
import Combine

class DevicesViewModel: ObservableObject {
    
    @Published var devices: [DeviceModel] = []

    private var cancellables = Set<AnyCancellable>()
    
    init(socketModel: DevicesWebSocketModel) {
        socketModel.$devices
            .receive(on: DispatchQueue.main)
            .assign(to: &$devices)
    }

    @Published var editingDeviceID: UUID? = nil
    @Published var editedName: String = ""
    @Published var responseChangeName: String?
    @Published var errorChangeName: String?
    
    private func findDevice(by id: UUID) -> DeviceModel? {
        return devices
            .first { $0.id == id } // Finds the first match
    }
    
    func toggleVisibility(idToToggle: UUID?) {
        guard let id = idToToggle,
              let index = devices.firstIndex(where: { $0.id == id }) else {
            print("Device not found.")
            return
        }

        devices[index].showInDashboard.toggle()
        print("Toggled visibility for device: \(devices[index].name)")
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
