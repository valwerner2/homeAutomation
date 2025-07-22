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
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= intervalMillis))
    {
        Serial.print(millis());
        Serial.println("Reconnecting to WiFi...");
        WiFi.disconnect();
        WiFi.reconnect();
        previousMillis = currentMillis;
    }
}

#endif //WIRELESSAHT20_WIFIRECONNECT_H
