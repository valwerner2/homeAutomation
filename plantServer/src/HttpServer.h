//
// Created by valwe on 26/04/2025.
//

#ifndef ESP32_PLANTSERVER_HTTPSERVER_H
#define ESP32_PLANTSERVER_HTTPSERVER_H

#pragma once

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

namespace PlantServer
{

    class HttpServer
    {
    private:
        AsyncWebServer server;
    public:
        HttpServer();
        void start();
    };

} // PlantServer

#endif //ESP32_PLANTSERVER_HTTPSERVER_H
