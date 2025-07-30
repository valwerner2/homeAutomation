//
// Created by valentinw on 22.07.25.
//

#ifndef WIRELESSAHT20_WIFIRECONNECT_H
#define WIRELESSAHT20_WIFIRECONNECT_H

#include <Arduino.h>
#include "WiFi.h"

void reconnectWifi(unsigned long intervalMillis)
{
    unsigned long currentMillis = millis();
    static unsigned long previousMillis = millis();

    // if WiFi is down, try reconnecting
    if ((currentMillis - previousMillis >= intervalMillis))
    {
        previousMillis = currentMillis;
        Serial.print("Checking Wifi: ");
        if(WiFi.status() != WL_CONNECTED)
        {
            Serial.print("disconnected\n");
            Serial.println("Reconnecting to WiFi...");
            WiFi.reconnect();
            return;
        }
        Serial.print("connected\n");

    }
}

#endif //WIRELESSAHT20_WIFIRECONNECT_H
