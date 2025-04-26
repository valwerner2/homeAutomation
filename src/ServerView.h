//
// Created by valwe on 26/04/2025.
//

#ifndef ESP32_PLANTSERVER_SERVERVIEW_H
#define ESP32_PLANTSERVER_SERVERVIEW_H

#pragma once

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "indexHtml.h"

namespace PlantServer
{

    class ServerView
    {
    private:
        AsyncWebServer server;
    public:
        ServerView();
        void start();
    };

} // PlantServer

#endif //ESP32_PLANTSERVER_SERVERVIEW_H
