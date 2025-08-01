	//
//  DeviceInfoModel.swift
//  iosApp
//
//  Created by Valentin Werner on 31.07.25.
//

import Foundation

struct DeviceModel: Identifiable, Decodable {
    let id = UUID()          // Needed for Identifiable
    let name: String
    let ip: String
    let mac: String
    let purpose: String
    let active: Bool

    enum CodingKeys: String, CodingKey {
        case name, ip, mac, purpose, active
    }
}
