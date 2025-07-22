//
// Created by valentinw on 17.07.25.
//

#ifndef PLANTSERVER_BROADCASTDEVICE_H
#define PLANTSERVER_BROADCASTDEVICE_H

#include <string>

#include "WiFi.h"

namespace IOT
{
    class DeviceBroadcaster
    {
    private:
        unsigned long lastBroadcast_ = 0;
        const char* broadcastIp_ = "255.255.255.255";
        char macAddr[18] = {0};
        const int udpPort_ = 4210;
        WiFiUDP udp_;
        String purpose_;

    public:
        DeviceBroadcaster(String purpose);
        void setup();
        void sendBroadcast();
        void sendBroadcast(const unsigned long msInterval);
    };
}

#endif //PLANTSERVER_BROADCASTDEVICE_H
