//
// Created by valwe on 08/12/2024.
//

#include "Output.h"
namespace PlantServer
{
    Output::Output(uint8_t pin, uint8_t outputMode, uint32_t value)
    {
        this->pin = pin;
        this->value = value;
        this->outputMode = outputMode;

        pinMode(this->pin, OUTPUT);
    }
    void Output::setValue(uint8_t value)
    {
        switch (this->outputMode)
        {
            case OUTPUT_DIGITAL:
                digitalWrite(this->pin, value);
                break;
            default:
                analogWrite(this->pin, value);
        }
    }

}