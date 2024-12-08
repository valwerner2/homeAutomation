//
// Created by valwe on 08/12/2024.
//

#ifndef ESP32_PLANTSERVER_GROWLIGHT_H
#define ESP32_PLANTSERVER_GROWLIGHT_H

#include "Output.h"

namespace PlantServer
{
    class GrowLight
    {
    private:
        Output pwm;
        Output relay;
        uint8_t brightness;
    public:
        GrowLight(uint8_t pinPwm, uint8_t pinRelay, uint8_t brightness = 0);
        void setBrightness(uint8_t brightness);
    };
}

#endif //ESP32_PLANTSERVER_GROWLIGHT_H
