//
// Created by valentinw on 31.07.25.
//

#ifndef PLANTSERVER_STATE_H
#define PLANTSERVER_STATE_H

#include <Preferences.h>
#include <ArduinoJson.h>

namespace PlantServer
{
    class State
    {
    public:
        static constexpr int opModeTimeBased = 0, opModeSlave  = 1, opModeServerSlaveOn = 2, opModeServerSlaveOff = 3;
    private:
        int opModeGrowLightTop_;
        int brightnessGrowLightTop_;
        int onTimeGrowLightTop_;
        int offTimeGrowLightTop_;

        int opModeGrowLightBottom_;
        int brightnessGrowLightBottom_;
        int onTimeGrowLightBottom_;
        int offTimeGrowLightBottom_;

        int opModeOutletLeft_;
        int onOutletLeft_;
        int onTimeOutletLeft_;
        int offTimeOutletLeft_;

        int opModeOutletRight_;
        int onOutletRight_;
        int onTimeOutletRight_;
        int offTimeOutletRight_;

        Preferences preferences_;
    public:
        State();
        void readState();
        void writeState();
        JsonDocument toJson();
        String toJsonString();

        // Grow Light Top
        int getOpModeGrowLightTop() const { return opModeGrowLightTop_; }
        void setOpModeGrowLightTop(int value)
        {
            opModeGrowLightTop_ = value;

            preferences_.begin("plantServer", false);
            preferences_.putInt("opModeGrowLightTop", opModeGrowLightTop_);
            preferences_.end();
        }

        int getBrightnessGrowLightTop() const { return brightnessGrowLightTop_; }
        void setBrightnessGrowLightTop(int value)
        {
            brightnessGrowLightTop_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("brightnessGrowLightTop", brightnessGrowLightTop_);
            preferences_.end();
        }

        int getOnTimeGrowLightTop() const { return onTimeGrowLightTop_; }
        void setOnTimeGrowLightTop(int value)
        {
            onTimeGrowLightTop_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("onTimeGrowLightTop", onTimeGrowLightTop_);
            preferences_.end();
        }

        int getOffTimeGrowLightTop() const { return offTimeGrowLightTop_; }
        void setOffTimeGrowLightTop(int value)
        {
            offTimeGrowLightTop_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("offTimeGrowLightTop", offTimeGrowLightTop_);
            preferences_.end();
        }

        // Grow Light Bottom
        int getOpModeGrowLightBottom() const { return opModeGrowLightBottom_; }
        void setOpModeGrowLightBottom(int value)
        {
            opModeGrowLightBottom_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("opModeGrowLightBottom", opModeGrowLightBottom_);
            preferences_.end();
        }

        int getBrightnessGrowLightBottom() const { return brightnessGrowLightBottom_; }
        void setBrightnessGrowLightBottom(int value)
        {
            brightnessGrowLightBottom_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("brightnessGrowLightBottom", brightnessGrowLightBottom_);
            preferences_.end();
        }

        int getOnTimeGrowLightBottom() const { return onTimeGrowLightBottom_; }
        void setOnTimeGrowLightBottom(int value)
        {
            onTimeGrowLightBottom_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("onTimeGrowLightBottom", onTimeGrowLightBottom_);
            preferences_.end();
        }

        int getOffTimeGrowLightBottom() const { return offTimeGrowLightBottom_; }
        void setOffTimeGrowLightBottom(int value)
        {
            offTimeGrowLightBottom_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("offTimeGrowLightBottom", offTimeGrowLightBottom_);
            preferences_.end();
        }

        // Outlet Left
        int getOpModeOutletLeft() const { return opModeOutletLeft_; }
        void setOpModeOutletLeft(int value)
        {
            opModeOutletLeft_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("opModeOutletLeft", opModeOutletLeft_);
            preferences_.end();
        }

        int getOnOutletLeft() const { return onOutletLeft_; }
        void setOnOutletLeft(int value)
        {
            onOutletLeft_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("onOutletLeft", onOutletLeft_);
            preferences_.end();
        }

        int getOnTimeOutletLeft() const { return onTimeOutletLeft_; }
        void setOnTimeOutletLeft(int value)
        {
            onTimeOutletLeft_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("onTimeOutletLeft", onTimeOutletLeft_);
            preferences_.end();
        }

        int getOffTimeOutletLeft() const { return offTimeOutletLeft_; }
        void setOffTimeOutletLeft(int value)
        {
            offTimeOutletLeft_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("offTimeOutletLeft", offTimeOutletLeft_);
            preferences_.end();
        }

        // Outlet Right
        int getOpModeOutletRight() const { return opModeOutletRight_; }
        void setOpModeOutletRight(int value)
        {
            opModeOutletRight_ = value;preferences_.begin("plantServer", false);
            preferences_.putInt("opModeOutletRight", opModeOutletRight_);
            preferences_.end();
        }

        int getOnOutletRight() const { return onOutletRight_; }
        void setOnOutletRight(int value)
        {
            onOutletRight_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("onOutletRight", onOutletRight_);
            preferences_.end();
        }

        int getOnTimeOutletRight() const { return onTimeOutletRight_; }
        void setOnTimeOutletRight(int value)
        {
            onTimeOutletRight_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("onTimeOutletRight", onTimeOutletRight_);
            preferences_.end();}

        int getOffTimeOutletRight() const { return offTimeOutletRight_; }
        void setOffTimeOutletRight(int value)
        {
            offTimeOutletRight_ = value;
            preferences_.begin("plantServer", false);
            preferences_.putInt("offTimeOutletRight", offTimeOutletRight_);
            preferences_.end();
        }
    };
}

#endif //PLANTSERVER_STATE_H
