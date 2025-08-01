//
//  DevicesView.swift
//  iosApp
//
//  Created by Valentin Werner on 31.07.25.
//
import SwiftUI

struct DevicesView: View {
    @StateObject private var viewModel = DevicesViewModel()
    
    
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
                            header:
                                Text(name)
                                        .font(.headline)
                                        .textCase(nil)
                        ) {
                            ForEach(devices) { device in
                                VStack{
                                    HStack{
                                        VStack(alignment: .leading, spacing: verticalSpacing) {
                                            
                                            Text("Purpose: \(device.purpose)")
                                            Text("IP: \(device.ip)")
                                            Text("MAC: \(device.mac)")
                                        }
                                        .padding(.vertical, verticalPadding)
                                        
                                        Spacer()
                                        
                                        VStack(alignment: .center, spacing: verticalSpacing) {
                                            Image(systemName: device.active ? "wifi" : "wifi.slash")
                                                .foregroundStyle(device.active ? activeColor : inactiveColor)
                                            
                                            Button(action: {
                                                // Your action goes here
                                                print("Eye button was pressed!")
                                            }) {
                                                Image(systemName: device.active ? "eye" : "eye.slash")
                                                    .foregroundStyle(device.active ? activeColor : inactiveColor)
                                            }
                                            .buttonStyle(.plain)
                                            
                                            Button(action: {
                                                if(device.active)
                                                {
                                                    // Your action goes here
                                                    print("Pencil button was pressed!")
                                                    if(viewModel.editingDeviceID == device.id) {viewModel.editingDeviceID = nil}
                                                    else {viewModel.editingDeviceID = device.id}
                                                    viewModel.editedName = device.name
                                                }
                                            }) {
                                                Image(systemName: "pencil")
                                                    .foregroundStyle(device.active ? activeColor : inactiveColor)
                                            }
                                            .buttonStyle(.plain)
                                            
                                        }
                                        .padding(.vertical, verticalPadding)
                                        
                                    }
                                    if viewModel.editingDeviceID == device.id{
                                        // Show TextField for editing purpose
                                        HStack{
                                            TextField("Edit purpose", text: $viewModel.editedName)
                                                .textFieldStyle(.roundedBorder)
                                            
                                            Button(action: {
                                                if(device.active)
                                                {
                                                    // Your action goes here
                                                    print("SEND button was pressed!")
                                                    viewModel.changeName()
                                                }
                                            }) {
                                                Image(systemName: "tray.and.arrow.down.fill")
                                                    .foregroundStyle(device.active ? activeColor : inactiveColor)
                                            }
                                            .buttonStyle(.plain)
                                        }
                                    }
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

#Preview {
    DevicesView()
}
