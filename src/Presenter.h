//
// Created by valwe on 26/04/2025.
//

#ifndef ESP32_PLANTSERVER_PRESENTER_H
#define ESP32_PLANTSERVER_PRESENTER_H

#include "httpServer.h"

namespace PlantServer
{

    class Presenter
    {
    private:
        httpServer serverView;
    public:
        Presenter();
        void start();
    };

} // PlantServer

#endif //ESP32_PLANTSERVER_PRESENTER_H
