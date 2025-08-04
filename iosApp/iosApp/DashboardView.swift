//
//  DashboardView.swift
//  iosApp
//
//  Created by Valentin Werner on 01.08.25.
//
import SwiftUI

struct DashboardView: View {
    
    @ObservedObject var viewModel: DashboardViewModel
    
    init(viewModel: DashboardViewModel){
        self.viewModel = viewModel
    }
    
    var body: some View {
        Text("Hello Dashboard")
    }
}
