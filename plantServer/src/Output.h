//
// Created by valwe on 08/12/2024.
//

#ifndef ESP32_PLANTSERVER_OUTPUT_H
#define ESP32_PLANTSERVER_OUTPUT_H

#include <Arduino.h>

namespace PlantServer
{
    enum outputModes
    {
        OUTPUT_ANALOG,
        OUTPUT_DIGITAL
    };
    class Output
    {
    private:
        uint8_t pin;
        uint8_t value;
        uint8_t outputMode;
    public:
        Output();
        Output(uint8_t pin, uint8_t outputMode = OUTPUT_ANALOG, uint32_t value = 0);
        void setValue(uint8_t value);
    };
}


#endif //ESP32_PLANTSERVER_OUTPUT_H
