//
// Created by valwe on 08/12/2024.
//

#include "GrowLight.h"

namespace PlantServer
{
    GrowLight::GrowLight(uint8_t pinPwm, uint8_t pinRelay, uint8_t brightness)
    {
        this->pwm = Output(pinPwm, OUTPUT_ANALOG, brightness);
        this->relay = Output(pinRelay, OUTPUT_DIGITAL, brightness);
        this->brightness = brightness;
    }
    void GrowLight::setBrightness(uint8_t brightness)
    {
        if(brightness > 100){brightness = 100;}

        if(!brightness)
        {
            this->pwm.setValue(255);
            this->relay.setValue(LOW);
        }
        else
        {
            this->pwm.setValue(map(brightness, 0, 100, 255, 0));
            this->relay.setValue(HIGH);
        }
        this->brightness = brightness;
    }
    uint8_t GrowLight::getBrightness()
    {
        return this->brightness;
    }

}