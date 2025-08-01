//
//  DashboardViewModel.swift
//  iosApp
//
//  Created by Valentin Werner on 01.08.25.
//
import Foundation
import Combine

class DashboardViewModel: ObservableObject
{
    
    @Published var groupedDevices: [String: [DeviceModel]] = [:]
    
    private var model: DevicesWebSocketModel
    private var cancellables = Set<AnyCancellable>()
    
    init(model: DevicesWebSocketModel = DevicesWebSocketModel()) {
        self.model = model
        
        model.$groupedDevices
            .receive(on: DispatchQueue.main)
            .assign(to: &$groupedDevices)
    }
}
