#pragma once

#include "game.h"

class Client{
public:
    void run();
private:
    int id = {0};
    Game game;
};
