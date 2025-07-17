#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_AHTX0 aht;

void initAHT(void);
void initScreen(void);

void setup()
{
    Serial.begin(115200);
    delay(1000);


    initAHT();
    initScreen();
}

void loop()
{
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);

    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity.relative_humidity);
    Serial.println(" %");

    display.clearDisplay();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Temp: ");
    display.print(temp.temperature);
    display.println(" C");

    display.print("Hum: ");
    display.print(humidity.relative_humidity);
    display.println(" %");
    display.display();

    delay(2000);

    delay(1000);
}
void initAHT(void)
{
    // Initialize I2C with correct pins
    Wire.begin(8, 9);

    if (!aht.begin(&Wire)) {
        Serial.println("Could not find AHT! Check wiring");
        while (1) delay(10);
    }
    Serial.println("AHT20 found");
}
void initScreen(void)
{
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