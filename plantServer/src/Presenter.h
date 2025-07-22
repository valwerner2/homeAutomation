//
// Created by valwe on 26/04/2025.
//

#ifndef ESP32_PLANTSERVER_PRESENTER_H
#define ESP32_PLANTSERVER_PRESENTER_H

#include "HttpServer.h"

namespace PlantServer
{

    class Presenter
    {
    private:
        HttpServer serverView;
    public:
        Presenter();
        void start();
    };

} // PlantServer

#endif //ESP32_PLANTSERVER_PRESENTER_H
