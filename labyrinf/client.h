#pragma once

#include "gameDrawable.h"

class Client{
public:
    void run();
private:
    int id = {0};
    GameDrawable game;
};
