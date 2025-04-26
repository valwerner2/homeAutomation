//
// Created by valwe on 08/12/2024.
//

#ifndef ESP32_PLANTSERVER_GLOBALS_H
#define ESP32_PLANTSERVER_GLOBALS_H


#include "GrowLight.h"


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "indexHtml.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

AsyncWebServer server(80);
const char* PARAM_INPUT = "value";
PlantServer::GrowLight growLightTop(6, 1);
PlantServer::GrowLight growLightBottom(7, 2);
PlantServer::Output PowerBarRight(3, PlantServer::outputModes::OUTPUT_DIGITAL, HIGH);
PlantServer::Output PowerBarLeft(4, PlantServer::outputModes::OUTPUT_DIGITAL, HIGH);

#define I2C_SDA 8  // Adjust to your board's wiring
#define I2C_SCL 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#endif //ESP32_PLANTSERVER_GLOBALS_H
