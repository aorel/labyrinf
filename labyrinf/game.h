#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

#include "command.h"

#include "labyrinth.h"
#include "player.h"


class Game{
public:
    Game() = default;//TODO on server side
    
    bool checkCommand(Command command);
    void applyCommand(Command command);//TODO

protected:
    Labyrinth labyrinth;
    std::vector<Player> players;
    Player currentPlayer;//TODO pointer to a player (Player *player)
    
    
};
