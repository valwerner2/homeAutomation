#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "WiFi.h"
#include "DeviceBroadcaster.h"
#include "wifiReconnect.h"
#include "wifiPassword.h"

Adafruit_AHTX0 aht;
IOT::DeviceBroadcaster broadcaster("ath20");
AsyncWebServer server(80);

void serverSetup();

void setup() {
    Serial.begin(115200);
    delay(5000);
    Wire.begin(8, 9);
    if (! aht.begin(&Wire)) {
        Serial.println("Could not find AHT? Check wiring");
        while (1) delay(10);
    }
    Serial.println("AHT20 found");

    WiFi.begin(ssid, password);
    char connectAnimationBuffer[] = "|/-\\";
    while (WiFi.status() != WL_CONNECTED) {
        for (int i = 0; i < strlen(connectAnimationBuffer); i++)
        {
            Serial.print(connectAnimationBuffer[i]);
            delay(100);
        }
    }
    Serial.println(" Connected!");
    Serial.println(WiFi.localIP());

    broadcaster.setup();
    serverSetup();
}

void loop() {
    reconnectWifi(5000);
    broadcaster.sendBroadcast(5000);
    delay(500);
}

void serverSetup()
{
    server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
        JsonDocument responseJson;
        sensors_event_t humidity, temp;
        aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

        responseJson["temperature"] = temp.temperature;
        responseJson["humidity"] = humidity.relative_humidity;

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->addHeader("Access-Control-Allow-Origin", "*");
        response->addHeader("code", 200);

        serializeJson(responseJson, *response);
        request->send(response);
    });
    server.begin();
}