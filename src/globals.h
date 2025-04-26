//
// Created by valwe on 08/12/2024.
//

#include "GrowLight.h"


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


#ifndef ESP32_PLANTSERVER_HTML_H
#define ESP32_PLANTSERVER_HTML_H
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


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>PlantServer</title>
    <style>
        html {font-family: Arial; display: inline-block; text-align: center;}
        h1 {font-size: 2.3rem; color: darkblue}
        h2 {font-size: 1.5rem; color: darkblue}
        p {font-size: 1.9rem;}
        body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
        .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: mediumspringgreen;
            outline: none; -webkit-transition: .2s; transition: opacity .2s;}
        .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: darkblue; cursor: pointer;}
        .slider::-moz-range-thumb { width: 35px; height: 35px; background: darkblue; cursor: pointer; }
    </style>
</head>
<body>
<h1>PlantServer</h1>
<h2>GrowLights</h2>
<p><span id="textSliderValue">%SLIDERGROWLIGHT1VALUE%</span></p>
<p><input type="range" onchange="updateSliderPWM(this)" id="sliderGrowLight1" min="0" max="100" value="%SLIDERGROWLIGHT1VALUE%" step="1" class="slider"></p>
<script>
    function updateSliderPWM(element) {
        var sliderValue = document.getElementById("sliderGrowLight1").value;
        document.getElementById("textSliderValue").innerHTML = sliderValue;
        console.log(sliderValue);
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/growLight1Brightness?value="+sliderValue, true);
        xhr.send();
    }
</script>
</body>
</html>
)rawliteral";

#endif //ESP32_PLANTSERVER_HTML_H
