#include "wifiPassword.h"
#include "GrowLight.h"
#include "httpServer.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

#define MYTZ "CET-1CEST-2,M3.5.0,M10.5.0/3"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

#define I2C_SDA 8
#define I2C_SCL 9

struct tm tInfo;

PlantServer::GrowLight growLightTop(6, 1);
PlantServer::GrowLight growLightBottom(7, 2);
PlantServer::Output PowerBarRight(3, PlantServer::outputModes::OUTPUT_DIGITAL, HIGH);
PlantServer::Output PowerBarLeft(4, PlantServer::outputModes::OUTPUT_DIGITAL, HIGH);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initScreen(void);
void initWifi();
void initTime();

uint16_t getIntTime();
void updateTime(const uint32_t timeout);

bool secondPassed();

void printTime()
{
    char str[30];
    strftime(str, sizeof(str), "%T", &tInfo);
    Serial.printf("%s %d\n", str, getIntTime());

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.printf("%s - %d\n", WiFi.localIP().toString(), WiFi.status());
    display.printf("%s %d\n", str, getIntTime());
    //display.printf("Top: %d\%\nBottom: %d\%\n", growLightTop.getBrightness(), growLightBottom.getBrightness());
    display.display();
}

PlantServer::httpServer server;


void setup()
{
    Serial.begin(115200);
    delay(5000);
    initScreen();
    initWifi();
    initTime();

    server.start();
}

void loop()
{
    if(secondPassed())
    {
        printTime();
    }
}

uint16_t getIntTime()
{
    char buffer[5];
    sprintf(buffer, "%2d%02d", tInfo.tm_hour, tInfo.tm_min);
    return atoi(buffer);
}
bool secondPassed()
{
    time_t now = time(nullptr);
    localtime_r(&now, &tInfo);

    static uint8_t old;
    if (tInfo.tm_sec != old) {
        old = tInfo.tm_sec;
        return true;
    }
    return false;
}

void initWifi()
{
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    char connectAnimationBuffer[] = "|/-\\";
    while (WiFi.status() != WL_CONNECTED) {
        for (int i = 0; i < strlen(connectAnimationBuffer); i++)
        {
            display.clearDisplay();
            display.setTextSize(4);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0, 0);
            display.print(connectAnimationBuffer[i]);
            display.display();
            Serial.print(connectAnimationBuffer[i]);
            delay(100);
        }
    }
    Serial.println(" Connected!");
    Serial.println(WiFi.localIP());

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(WiFi.localIP());
    display.display();
}
void initTime()
{
    configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
    updateTime(5000);
}
void initScreen(void)
{
    Serial.println("Screen init start");
    Wire.begin(I2C_SDA, I2C_SCL);
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    display.clearDisplay();
    display.drawPixel(10, 10, SSD1306_WHITE);
    display.display();

    Serial.println("Screen init done");
    delay(2000);
}
void updateTime(const uint32_t timeout) {
    uint32_t start = millis();
    do {
        time_t now = time(nullptr);
        tInfo = *localtime(&now);
        delay(1);
    } while (millis() - start < timeout  && tInfo.tm_year <= (1970 - 1900));
}