//
//  DevicesView.swift
//  iosApp
//
//  Created by Valentin Werner on 31.07.25.
//
import SwiftUI

struct DevicesView: View {
    @ObservedObject var viewModel: DevicesViewModel
    
    
    let verticalSpacing: CGFloat = 16
    let verticalPadding: CGFloat = 4
    let activeColor = Color.blue
    let inactiveColor = Color.gray
    
    init(viewModel: DevicesViewModel){
        self.viewModel = viewModel
    }
    
    var body: some View {
        NavigationStack {
            List {
                ForEach(viewModel.devices) { currentDevice in
                        Section(
                            header:
                                Text(currentDevice.name)
                                        .font(.headline)
                                        .textCase(nil)
                        ) {
                            VStack{
                                HStack{
                                    VStack(alignment: .leading, spacing: verticalSpacing) {
                                        
                                        Text("Purpose: \(currentDevice.purpose)")
                                        Text("IP: \(currentDevice.ip)")
                                        Text("MAC: \(currentDevice.mac)")
                                    }
                                    .padding(.vertical, verticalPadding)
                                    
                                    Spacer()
                                    
                                    VStack(alignment: .center, spacing: verticalSpacing) {
                                        Image(systemName: currentDevice.active ? "wifi" : "wifi.slash")
                                            .frame(width: 20, height: 20)
                                            .contentTransition(.symbolEffect(.replace))
                                            .foregroundStyle(currentDevice.active ? activeColor : inactiveColor)
                                        
                                        Button(action: {
                                            print("Eye button was pressed!")
                                            withAnimation(.easeInOut) {
                                                viewModel.toggleVisibility(idToToggle: currentDevice.id)
                                            }
                                        }) {
                                            Image(systemName: currentDevice.showInDashboard ? "eye" : "eye.slash")
                                                .frame(width: 20, height: 20)
                                                .contentTransition(.symbolEffect(.replace))
                                                .foregroundStyle(currentDevice.showInDashboard ? activeColor : inactiveColor)
                                        }
                                        .buttonStyle(.plain)
                                        
                                        Button(action: {
                                            if(currentDevice.active)
                                            {
                                                // Your action goes here
                                                print("Pencil button was pressed!")
                                                if(viewModel.editingDeviceID == currentDevice.id) {viewModel.editingDeviceID = nil}
                                                else {viewModel.editingDeviceID = currentDevice.id}
                                                viewModel.editedName = currentDevice.name
                                            }
                                        }) {
                                            Image(systemName: currentDevice.active ? "pencil" : "pencil.slash")
                                                .frame(width: 20, height: 20)
                                                .contentTransition(.symbolEffect(.replace))
                                                .foregroundStyle(currentDevice.active ? activeColor : inactiveColor)
                                        }
                                        .buttonStyle(.plain)
                                        
                                    }
                                    .padding(.vertical, verticalPadding)
                                    
                                }
                                if viewModel.editingDeviceID == currentDevice.id{
                                    // Show TextField for editing purpose
                                    HStack{
                                        TextField("Edit purpose", text: $viewModel.editedName)
                                            .textFieldStyle(.roundedBorder)
                                        
                                        Button(action: {
                                            if(currentDevice.active)
                                            {
                                                // Your action goes here
                                                print("SEND button was pressed!")
                                                viewModel.changeName()
                                            }
                                        }) {
                                            Image(systemName: "tray.and.arrow.down.fill")
                                                .foregroundStyle(currentDevice.active ? activeColor : inactiveColor)
                                        }
                                        .buttonStyle(.plain)
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
    DevicesView(viewModel: DevicesViewModel(socketModel: DevicesWebSocketModel()))
}
