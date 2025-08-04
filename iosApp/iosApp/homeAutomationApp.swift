//
//  iosAppApp.swift
//  iosApp
//
//  Created by Valentin Werner on 21.07.25.
//

import SwiftUI

@main
struct homeAutomation: App {
    @StateObject private var socketModel: DevicesWebSocketModel
    private let connectedViewModel: ConnectedViewModel
    private let dashboardViewModel: DashboardViewModel
    private let devicesViewModel: DevicesViewModel

    init() {
        let socketModel = DevicesWebSocketModel()
        _socketModel = StateObject(wrappedValue: socketModel)

        self.connectedViewModel = ConnectedViewModel(socketModel: socketModel)
        self.dashboardViewModel = DashboardViewModel(socketModel: socketModel)
        self.devicesViewModel = DevicesViewModel(socketModel: socketModel)
    }

    var body: some Scene {
        WindowGroup {
            MainView(
                connectedView: ConnectedView(viewModel: connectedViewModel),
                dashboardView: DashboardView(viewModel: dashboardViewModel),
                devicesView: DevicesView(viewModel: devicesViewModel)
            )
        }
    }
}
