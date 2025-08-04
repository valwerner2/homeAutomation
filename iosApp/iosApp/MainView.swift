//
//  ContentView.swift
//  iosApp
//
//  Created by Valentin Werner on 21.07.25.
//

import SwiftUI

struct MainView: View {
    var devicesView: DevicesView
    var dashboardView: DashboardView
    
    init(devicesView: DevicesView, dashboardView: DashboardView) {
        self.devicesView = devicesView
        self.dashboardView = dashboardView
    }
    
    var body: some View {
        TabView {
                self.dashboardView
                    .tabItem{
                        Label("Dashboard", systemImage: "rectangle.grid.1x2")
                    }
            
                NavigationStack {
                    List {
                        NavigationLink("Go to View A", destination: ViewA())
                        NavigationLink("Go to View B", destination: ViewB())
                        NavigationLink("Go to View C", destination: ViewC())
                    }
                    .navigationTitle("Services")
                }
                    .tabItem {
                        Label("Services", systemImage: "square.stack.3d.up")
                    }
                
                self.devicesView
                    .tabItem {
                        Label("Devices", systemImage: "sensor")
                    }
            }
        
    }
        
}
struct ViewA: View {
    var body: some View {
        Text("This is View A")
            .navigationTitle("View A")
    }
}

struct ViewB: View {
    var body: some View {
        Text("This is View B")
            .navigationTitle("View B")
    }
}

struct ViewC: View {
    var body: some View {
        Text("This is View C")
            .navigationTitle("View C")
    }
}

    
#Preview {
    MainView(devicesView: DevicesView(viewModel: DevicesViewModel(socketModel: DevicesWebSocketModel())), dashboardView: DashboardView(viewModel: DashboardViewModel(socketModel: DevicesWebSocketModel())))
}
