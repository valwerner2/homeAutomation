//
// Created by valentinw on 17.07.25.
//

#include "DeviceBroadcaster.h"


namespace IOT
{
    DeviceBroadcaster::DeviceBroadcaster(String purpose)
    {
        purpose_ = purpose;
    }

    void DeviceBroadcaster::setup()
    {
        while (WiFi.status() != WL_CONNECTED) { delay(500);}

        udp_.begin(udpPort_);
    }

    void DeviceBroadcaster::sendBroadcast()
    {
        //wifi not connected
        if (WiFi.status() != WL_CONNECTED) {return;}

        String message = "{\"ip\": \"" + WiFi.localIP().toString() + "\", \"purpose\": \""+ purpose_ +"\"}";
        udp_.beginPacket(broadcastIp_, udpPort_);
        udp_.write((const uint8_t*)message.c_str(), message.length());
        udp_.endPacket();
    }

    void DeviceBroadcaster::sendBroadcast(const unsigned long msInterval)
    {
        unsigned long now = millis();
        if (now - lastBroadcast_ >= msInterval)
        {
            lastBroadcast_ = now;
            sendBroadcast();
        }
    }
}
#include "DeviceBroadcaster.h"
