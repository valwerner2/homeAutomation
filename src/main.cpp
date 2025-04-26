#include "globals.h"

#include "wifiPassword.h"

#include <Preferences.h>

#define MYTZ "CET-1CEST-2,M3.5.0,M10.5.0/3"

Preferences preferences;

struct tm tInfo;

uint16_t getIntTime();
char minutePassed();
char secondPassed();
void initWifi();
void updateTime(const uint32_t timeout);
void initTime();
void initServer();
void initScreen(void);

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
    display.printf("Top: %d\%\nBottom: %d\%\n", growLightTop.getBrightness(), growLightBottom.getBrightness());
    display.display();
}

void setup()
{
    Serial.begin(115200);
    delay(5000);
    initScreen();
    initWifi();
    initServer();
    initTime();

    preferences.begin("growLightTop", true); // "true" means read-only mode
    growLightTop.setBrightness(preferences.getUInt("brightness", 100));
    preferences.end();

    preferences.begin("growLightBottom", true); // "true" means read-only mode
    growLightBottom.setBrightness(preferences.getUInt("brightness", 100));
    preferences.end();
}

void loop()
{
    if(secondPassed())
    {
        printTime();
        if(getIntTime() >= 2359 || getIntTime() < 600)
        {
            growLightTop.setBrightness(0);
            growLightBottom.setBrightness(0);
        }
        else if(getIntTime() >= 600)
        {
            preferences.begin("growLightTop", true); // "true" means read-only mode
            growLightTop.setBrightness(preferences.getUInt("brightness", 100));
            preferences.end();

            preferences.begin("growLightBottom", true); // "true" means read-only mode
            growLightBottom.setBrightness(preferences.getUInt("brightness", 100));
            preferences.end();
        }

    }
}

uint16_t getIntTime()
{
    char buffer[5];
    sprintf(buffer, "%2d%02d", tInfo.tm_hour, tInfo.tm_min);
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

void initServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        auto callback = [](const String& var)
        {
            if(var == "SLIDERGROWLIGHT1VALUE")
            {
                preferences.begin("growLightTop", true); // "true" means read-only mode
                uint8_t temp = preferences.getUInt("brightness", 100);
                preferences.end();
                return String(temp);
            }
            return String();
        };
        request->send_P(200, "text/html", index_html, callback);
    });

    server.on("/growLight1Brightness", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String inputMessage;
        if (request->hasParam(PARAM_INPUT)) {
            inputMessage = request->getParam(PARAM_INPUT)->value();
            growLightBottom.setBrightness((uint8_t)inputMessage.toInt());
            growLightTop.setBrightness((uint8_t)inputMessage.toInt());

            preferences.begin("growLightTop", false); // "false" means read+write mode
            preferences.putUInt("brightness", (uint8_t)inputMessage.toInt()); // Store a uint value (0-255)
            preferences.end(); // Always end to free up the flash system

            preferences.begin("growLightBottom", false); // "false" means read+write mode
            preferences.putUInt("brightness", (uint8_t)inputMessage.toInt()); // Store a uint value (0-255)
            preferences.end(); // Always end to free up the flash system
        }
        else {
            inputMessage = "No message sent";
        }
        Serial.println(inputMessage);
        request->send(200, "text/plain", "OK");
    });

    server.begin();
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
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
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