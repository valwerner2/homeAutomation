//
// Created by valwe on 26/04/2025.
//

#include "ServerView.h"

const char* PARAM_INPUT = "value";

namespace PlantServer
{
    ServerView::ServerView() : server(80) {}

// Start the server
    void ServerView::start()
    {
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
            auto callback = [](const String& var)
            {
                if(var == "SLIDERGROWLIGHT1VALUE")
                {
                    /*
                    preferences.begin("growLightTop", true); // "true" means read-only mode
                    uint8_t temp = preferences.getUInt("brightness", 100);
                    preferences.end();
                     */
                    return String(100);
                }
                return String();
            };
            request->send_P(200, "text/html", index_html, callback);
        });

        server.on("/growLight1Brightness", HTTP_GET, [] (AsyncWebServerRequest *request) {
            String inputMessage;
            if (request->hasParam(PARAM_INPUT)) {
                inputMessage = request->getParam(PARAM_INPUT)->value();
                /*
                growLightBottom.setBrightness((uint8_t)inputMessage.toInt());
                growLightTop.setBrightness((uint8_t)inputMessage.toInt());

                preferences.begin("growLightTop", false); // "false" means read+write mode
                preferences.putUInt("brightness", (uint8_t)inputMessage.toInt()); // Store a uint value (0-255)
                preferences.end(); // Always end to free up the flash system

                preferences.begin("growLightBottom", false); // "false" means read+write mode
                preferences.putUInt("brightness", (uint8_t)inputMessage.toInt()); // Store a uint value (0-255)
                preferences.end(); // Always end to free up the flash system
                 */
            }
            else {
                inputMessage = "No message sent";
            }
            Serial.println(inputMessage);
            request->send(200, "text/plain", "OK");
        });

        server.begin();
    }
} // PlantServer