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
    
    private var timerCancellable: AnyCancellable?
    
    init(model: DevicesWebSocketModel = DevicesWebSocketModel()) {
        self.model = model
        
        model.$groupedDevices
            .receive(on: DispatchQueue.main)
            .assign(to: &$groupedDevices)
        
        startTimer()
    }
        
        private func startTimer() {
            timerCancellable = Timer
                .publish(every: 5, on: .main, in: .common)
                .autoconnect()
                .sink { [weak self] _ in
                    self?.pollDevices()
                }
        }

        private func pollDevices() {
            //TODO: send request to get info from devices
        }
        
        deinit {
            timerCancellable?.cancel()
        }
    
}
