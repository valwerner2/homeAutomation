//
// Created by valwe on 26/04/2025.
//

#include "Presenter.h"

namespace PlantServer
{
    Presenter::Presenter() {}

    void Presenter::start()
    {
        this->serverView.start();
    }
} // PlantServer