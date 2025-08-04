//
//  ConnectedToSocketView.swift
//  iosApp
//
//  Created by Valentin Werner on 04.08.25.
//

import SwiftUI

struct ConnectedView: View{
    
    @ObservedObject var viewModel: ConnectedViewModel
    
    init(viewModel: ConnectedViewModel){
        self.viewModel = viewModel
    }
    
    var body: some View {
            if viewModel.showConnectionState {
                HStack(spacing: 8) {
                    Image(systemName: viewModel.isConnected ? "wifi" : "wifi.slash")
                    Text(viewModel.isConnected ? "Connected" : "Reconnecting")
                }
                .padding(10)
                .frame(maxWidth: .infinity, alignment: .center)
                .background(viewModel.isConnected ? Color.green : Color.red)
                .cornerRadius(8)
            }
        }
}



#Preview {
    ConnectedView(viewModel: ConnectedViewModel(socketModel: DevicesWebSocketModel()))
}
