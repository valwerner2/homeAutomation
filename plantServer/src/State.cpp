//
// Created by valentinw on 31.07.25.
//

#include "State.h"

namespace PlantServer
{
    State::State(){}

    void State::readState()
    {
        // read-mode
        preferences_.begin("plantServer", true);

        opModeGrowLightTop_ = preferences_.getInt("opModeGrowLightTop", opModeSlave);
        opModeGrowLightBottom_ = preferences_.getInt("opModeGrowLightBottom", opModeSlave);
        opModeOutletLeft_ = preferences_.getInt("opModeOutletLeft", opModeSlave);
        opModeOutletRight_ = preferences_.getInt("opModeOutletRight", opModeSlave);

        brightnessGrowLightTop_ = preferences_.getInt("brightnessGrowLightTop", 100);
        onTimeGrowLightTop_ = preferences_.getInt("onTimeGrowLightTop", 100);
        offTimeGrowLightTop_ = preferences_.getInt("offTimeGrowLightTop", 100);

        brightnessGrowLightBottom_ = preferences_.getInt("brightnessGrowLightBottom", 100);
        onTimeGrowLightBottom_ = preferences_.getInt("onTimeGrowLightBottom", 100);
        offTimeGrowLightBottom_ = preferences_.getInt("offTimeGrowLightBottom", 100);

        onOutletLeft_ = preferences_.getInt("onOutletLeft", 1);
        onTimeOutletLeft_ = preferences_.getInt("onTimeOutletLeft", 100);
        offTimeOutletLeft_ = preferences_.getInt("offTimeOutletLeft", 100);

        onOutletRight_ = preferences_.getInt("onOutletRight", 1);
        onTimeOutletRight_ = preferences_.getInt("onTimeOutletRight", 100);
        offTimeOutletRight_ = preferences_.getInt("offTimeOutletRight", 100);

        preferences_.end();
    }

    void State::writeState()
    {
        // write mode
        preferences_.begin("plantServer", false);

        preferences_.putInt("opModeGrowLightTop", opModeGrowLightTop_);
        preferences_.putInt("opModeGrowLightBottom", opModeGrowLightBottom_);
        preferences_.putInt("opModeOutletLeft", opModeOutletLeft_);
        preferences_.putInt("opModeOutletRight", opModeOutletRight_);

        preferences_.putInt("brightnessGrowLightTop", brightnessGrowLightTop_);
        preferences_.putInt("onTimeGrowLightTop", onTimeGrowLightTop_);
        preferences_.putInt("offTimeGrowLightTop", offTimeGrowLightTop_);

        preferences_.putInt("brightnessGrowLightBottom", brightnessGrowLightBottom_);
        preferences_.putInt("onTimeGrowLightBottom", onTimeGrowLightBottom_);
        preferences_.putInt("offTimeGrowLightBottom", offTimeGrowLightBottom_);

        preferences_.putInt("onOutletLeft", onOutletLeft_);
        preferences_.putInt("onTimeOutletLeft", onTimeOutletLeft_);
        preferences_.putInt("offTimeOutletLeft", offTimeOutletLeft_);

        preferences_.putInt("onOutletRight", onOutletRight_);
        preferences_.putInt("onTimeOutletRight", onTimeOutletRight_);
        preferences_.putInt("offTimeOutletRight", offTimeOutletRight_);

        preferences_.end();
    }

    JsonDocument State::toJson()
    {
        JsonDocument doc;
        doc["opModeSlave"] = opModeSlave;
        doc["opModeServerSlave"] = opModeServerSlave;
        doc["opModeTimeBased"] = opModeTimeBased;

        doc["opModeGrowLightTop"] = opModeGrowLightTop_;
        doc["opModeGrowLightBottom"] = opModeGrowLightBottom_;
        doc["opModeOutletLeft"] = opModeOutletLeft_;
        doc["opModeOutletRight"] = opModeOutletRight_;

        doc["brightnessGrowLightTop"] = brightnessGrowLightTop_;
        doc["onTimeGrowLightTop"] = onTimeGrowLightTop_;
        doc["offTimeGrowLightTop"] = offTimeGrowLightTop_;

        doc["brightnessGrowLightBottom"] = brightnessGrowLightBottom_;
        doc["onTimeGrowLightBottom"] = onTimeGrowLightBottom_;
        doc["offTimeGrowLightBottom"] = offTimeGrowLightBottom_;

        doc["onOutletLeft"] = onOutletLeft_;
        doc["onTimeOutletLeft"] = onTimeOutletLeft_;
        doc["offTimeOutletLeft"] = offTimeOutletLeft_;

        doc["onOutletRight"] = onOutletRight_;
        doc["onTimeOutletRight"] = onTimeOutletRight_;
        doc["offTimeOutletRight"] = offTimeOutletRight_;

        return doc;
    }
    String State::toJsonString()
    {
        String jsonString;
        serializeJson(this->toJson(), jsonString);

        return jsonString;
    }
}