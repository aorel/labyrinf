#pragma once

#include <SFML/Graphics.hpp>

#include "command.h"

#include "labyrinth.h"
#include "player.h"

class Game
{
public:
    //Game();//TODO
protected:
    Labyrinth labyrinth;
    Player player;
};
