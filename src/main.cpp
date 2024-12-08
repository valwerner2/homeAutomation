#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "wifiPassword.h"
#include "html.h"

#define MYTZ "CET-1CEST-2,M3.5.0,M10.5.0/3"


struct tm tInfo;
typedef struct structGrowLight
{
    int turnOnTime;
    int turnOffTime;
    int maxBrightness;
    int dimTime;
}growLight;

int getIntTime();
char minutePassed();
char secondPassed();
void initWifi();
void updateTime(const uint32_t timeout);
void initTime();

void printTime()
{
    char str[30];
    strftime(str, sizeof(str), "%T", &tInfo);
    Serial.printf("%s %d\n", str, getIntTime());
}

void setup()
{
    Serial.begin(115200);
    initWifi();
    initTime();
}

void loop()
{
    if(secondPassed())
    {
        printTime();
    }
}

int getIntTime()
{
    char buffer[5];
    sprintf(buffer, "%2d%2d", tInfo.tm_hour, tInfo.tm_min);
    return atoi(buffer);
}
char minutePassed()
{
    time_t now = time(nullptr);
    localtime_r(&now, &tInfo);

    static uint8_t old;
    if (tInfo.tm_min != old) {
        old = tInfo.tm_min;
        return 1;
    }
    return 0;
}
char secondPassed()
{
    time_t now = time(nullptr);
    localtime_r(&now, &tInfo);

    static uint8_t old;
    if (tInfo.tm_sec != old) {
        old = tInfo.tm_sec;
        return 1;
    }
    return 0;
}
void initWifi()
{
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println(" Connected!");
}
void initTime()
{
    configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
    updateTime(5000);
}
void updateTime(const uint32_t timeout) {
    uint32_t start = millis();
    do {
        time_t now = time(nullptr);
        tInfo = *localtime(&now);
        delay(1);
    } while (millis() - start < timeout  && tInfo.tm_year <= (1970 - 1900));
}