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

    init() {
        let socketModel = DevicesWebSocketModel()
        _socketModel = StateObject(wrappedValue: socketModel)
    }

    var body: some Scene {
        WindowGroup {
            MainView(devicesView: DevicesView(viewModel: DevicesViewModel(socketModel: socketModel)),
                     dashboardView: DashboardView(viewModel: DashboardViewModel(socketModel: socketModel)))
        }
    }
}
