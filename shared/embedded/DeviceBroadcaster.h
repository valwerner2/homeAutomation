//
// Created by valentinw on 17.07.25.
//

#ifndef PLANTSERVER_BROADCASTDEVICE_H
#define PLANTSERVER_BROADCASTDEVICE_H

#include <Arduino.h>
#include <string>
#include <Preferences.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "WiFi.h"

namespace IOT
{
    class DeviceBroadcaster
    {
    private:
        unsigned long lastBroadcast_ = 0;
        const char* broadcastIp_ = "255.255.255.255";
        char macAddr_[18] = {0};
        const int udpPort_ = 4210;
        String name_;
        WiFiUDP udp_;
        String purpose_;
        Preferences preferences_;

    public:
        DeviceBroadcaster(String purpose, String name);
        DeviceBroadcaster(String purpose);
        void setup(AsyncWebServer& server);
        void sendBroadcast();
        void sendBroadcast(const unsigned long msInterval);
        void setName(String name);
    private:
        void loadName();
        void storeName();
    };
}

#endif //PLANTSERVER_BROADCASTDEVICE_H
