#include "wifiPassword.h"
#include "GrowLight.h"
#include "DeviceBroadcaster.h"
#include "State.h"
#include "wifiReconnect.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

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
PlantServer::Output outletRight(3, PlantServer::outputModes::OUTPUT_DIGITAL, HIGH);
PlantServer::Output outletLeft(4, PlantServer::outputModes::OUTPUT_DIGITAL, HIGH);
PlantServer::State state;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

AsyncWebServer server(80);

void initScreen(void);
void initWifi();
void initTime();
void initServer();
void updateGrowLights();
void updateOutlets();

bool isMissingParam(AsyncWebServerRequest *request, std::list<String> requiredParam);
bool isInOnTime(int onTime, int offTime);

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
    display.printf("%s - %d\n", WiFi.localIP().toString().c_str(), WiFi.status());
    display.printf("%s %d\n", str, getIntTime());
    //display.printf("Top: %d\%\nBottom: %d\%\n", growLightTop.getBrightness(), growLightBottom.getBrightness());
    display.display();
}


IOT::DeviceBroadcaster broadcaster("plantServer");

void setup()
{
    Serial.begin(115200);
    delay(5000);
    initScreen();
    initWifi();
    initTime();
    broadcaster.setup(server);
    state.readState();

    initServer();
}

void loop()
{
    reconnectWifi(5000);
    if(secondPassed())
    {
        printTime();
    }
    broadcaster.sendBroadcast(5000);
    updateGrowLights();
    updateOutlets();
}

bool isInOnTime(int onTime, int offTime)
{
    int current = getIntTime();

    if(onTime < offTime)
    {
        return onTime <= current  && current <= offTime;
    }
    if(onTime > offTime)
    {
      return  (onTime <= current  && current <= 2359) || (0000 <= current  && current <= offTime);
    }
    return false;
}

void updateGrowLights()
{
    //growLightTop
}
void updateOutlets()
{
    //left
    bool outletLeftOn = false;
    switch(state.getOpModeOutletLeft())
    {
        case state.opModeTimeBased:
            outletLeftOn = isInOnTime(state.getOnTimeOutletLeft(), state.getOffTimeOutletLeft());
            break;
        case state.opModeSlave:

            break;
        default:
            if(WiFi.status() == WL_CONNECTED)
            {
                outletLeftOn = state.getOnOutletLeft();
            }
            else
            {
                outletLeftOn = state.getOpModeOutletLeft() == state.opModeServerSlaveOn;
            }
            break;
    }
    if(outletLeftOn){ outletLeft.setValue(HIGH); }else{ outletLeft.setValue(LOW); }

}

void initServer()
{
    server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->addHeader("Access-Control-Allow-Origin", "*");

        response->print(state.toJsonString());

        request->send(response);
    });

    server.on("/growLightTop", HTTP_PUT, [] (AsyncWebServerRequest *request) {
        std::list<String> requiredParam = {"opModeGrowLightTop",
                                           "brightnessGrowLightTop",
                                           "onTimeGrowLightTop",
                                           "offTimeGrowLightTop"};

        if(isMissingParam(request, requiredParam)){return;}

        String newName = request->getParam("name", true)->value();

        state.setOpModeGrowLightTop(request->getParam("opModeGrowLightTop", true)->value().toInt());
        state.setBrightnessGrowLightTop(request->getParam("brightnessGrowLightTop", true)->value().toInt());
        state.setOnTimeGrowLightTop(request->getParam("onTimeGrowLightTop", true)->value().toInt());
        state.setOffTimeGrowLightTop(request->getParam("offTimeGrowLightTop", true)->value().toInt());

        request->send(200, "application/json", "{\"status\":\"growLightTop updated\"}");
    });

    server.on("/growLightBottom", HTTP_PUT, [] (AsyncWebServerRequest *request) {
        std::list<String> requiredParam = {"opModeGrowLightBottom",
                                           "brightnessGrowLightBottom",
                                           "onTimeGrowLightBottom",
                                           "offTimeGrowLightBottom"};

        if(isMissingParam(request, requiredParam)){return;}

        String newName = request->getParam("name", true)->value();

        state.setOpModeGrowLightBottom(request->getParam("opModeGrowLightBottom", true)->value().toInt());
        state.setBrightnessGrowLightBottom(request->getParam("brightnessGrowLightBottom", true)->value().toInt());
        state.setOnTimeGrowLightBottom(request->getParam("onTimeGrowLightBottom", true)->value().toInt());
        state.setOffTimeGrowLightBottom(request->getParam("offTimeGrowLightBottom", true)->value().toInt());

        request->send(200, "application/json", "{\"status\":\"growLightBottom updated\"}");
    });

    server.on("/outletLeft", HTTP_PUT, [] (AsyncWebServerRequest *request) {
        std::list<String> requiredParam = {"opModeOutletLeft",
                                           "onOutletLeft",
                                           "onTimeOutletLeft",
                                           "offTimeOutletLeft"};

        if(isMissingParam(request, requiredParam)){return;}

        String newName = request->getParam("name", true)->value();

        state.setOpModeOutletLeft(request->getParam("opModeOutletLeft", true)->value().toInt());
        state.setOnOutletLeft(request->getParam("onOutletLeft", true)->value().toInt());
        state.setOnTimeOutletLeft(request->getParam("onTimeOutletLeft", true)->value().toInt());
        state.setOffTimeOutletLeft(request->getParam("offTimeOutletLeft", true)->value().toInt());

        request->send(200, "application/json", "{\"status\":\"outletLeft updated\"}");
    });

    server.on("/outletRight", HTTP_PUT, [] (AsyncWebServerRequest *request) {
        std::list<String> requiredParam = {"opModeOutletRight",
                                           "onOutletRight",
                                           "onTimeOutletRight",
                                           "offTimeOutletRight"};

        if(isMissingParam(request, requiredParam)){return;}

        String newName = request->getParam("name", true)->value();

        state.setOpModeOutletRight(request->getParam("opModeOutletRight", true)->value().toInt());
        state.setOnOutletRight(request->getParam("onOutletRight", true)->value().toInt());
        state.setOnTimeOutletRight(request->getParam("onTimeOutletRight", true)->value().toInt());
        state.setOffTimeOutletRight(request->getParam("offTimeOutletRight", true)->value().toInt());

        request->send(200, "application/json", "{\"status\":\"outletRight updated\"}");
    });

    server.begin();
}

bool isMissingParam(AsyncWebServerRequest *request, std::list<String> requiredParam)
{
    bool missing = false;
    std::list<String> missingParam = {};

    for(auto param : requiredParam)
    {
        if (!request->hasParam(param, true))
        {
            missingParam.push_back(param);
        }
    }

    missing = !missingParam.empty();
    if(missing)
    {

        String stringMissingParam = "(";
        for(auto param : missingParam)
        {
            stringMissingParam += param + ", ";
        }
        stringMissingParam += ")";
        request->send(400, "application/json", "{\"error\":\"Missing parameters " +stringMissingParam+"\"}");
    }

    return missing;
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