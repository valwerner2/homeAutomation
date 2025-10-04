//
//  MainView.swift
//  openFarmer
//
//  Created by Valentin Werner on 04.10.25.
//

import SwiftUI
import SwiftData

struct MainView: View {

    var body: some View {
        TabView{
            Tab("info", systemImage: "info") {
                Text("infos")
            }
            .badge("hello world")
            Tab("lights", systemImage: "lightbulb.max"){
                Text("lights")
            }
            Tab("sensors", systemImage: "sensor"){
                Text("sensors")
            }
            Tab("settings", systemImage: "gear"){
                Text("settings")
            }
            
        }
    }
}

#Preview {
    MainView()
        .modelContainer(for: [], inMemory: true)
}
