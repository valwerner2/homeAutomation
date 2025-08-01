//
//  ContentView.swift
//  iosApp
//
//  Created by Valentin Werner on 21.07.25.
//

import SwiftUI

struct ContentView: View {
    
    var body: some View {
        TabView {
            Text("Overview")
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
                
                DevicesView()
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
    ContentView()
}
