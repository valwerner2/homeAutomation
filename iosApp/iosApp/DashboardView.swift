//
//  DashboardView.swift
//  iosApp
//
//  Created by Valentin Werner on 01.08.25.
//
import SwiftUI

struct DashboardView: View {
    @StateObject private var viewModel = DevicesViewModel()
    
    var body: some View {
        Text("Hello Dashboard")
    }
}
