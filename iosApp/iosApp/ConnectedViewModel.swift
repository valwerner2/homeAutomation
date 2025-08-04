//
//  ConnectedViewModel.swift
//  iosApp
//
//  Created by Valentin Werner on 04.08.25.
//
import Foundation
import Combine
import SwiftUICore


class ConnectedViewModel: ObservableObject {
    
    @Published var isConnected: Bool = false
    @Published var showConnectionState: Bool = true
    var lastConnectionState = false
    
    private var cancellables = Set<AnyCancellable>()
    private var hideConnectionStateWorkItem: DispatchWorkItem?
    
    init(socketModel: DevicesWebSocketModel) {
        print("connection init")
        
        socketModel.$isConnected
            .receive(on: DispatchQueue.main)
            .sink { [weak self] connected in
                guard let self = self else { return }
                self.isConnected = connected
                
                let previousConnectionState = self.lastConnectionState
                self.lastConnectionState = connected
                
                print("last:", previousConnectionState)
                print("curr:", connected)
                
                if previousConnectionState != connected {
                    if connected {
                        self.showConnectionState = true
                        
                        // Cancel any previous scheduled task
                        self.hideConnectionStateWorkItem?.cancel()
                        
                        // Schedule to hide after 5 seconds
                        let workItem = DispatchWorkItem { [weak self] in
                            self?.showConnectionState = false
                        }
                        self.hideConnectionStateWorkItem = workItem
                        DispatchQueue.main.asyncAfter(deadline: .now() + 5, execute: workItem)
                        
                    } else {
                        // Immediately show when disconnected
                        self.showConnectionState = true
                        
                        // Cancel any pending hide task
                        self.hideConnectionStateWorkItem?.cancel()
                    }
                }
            }
            .store(in: &cancellables)
    }
}
