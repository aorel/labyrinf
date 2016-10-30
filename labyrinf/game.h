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
    Game(CommandFunction vCC);//TODO
    
    bool checkCommand(Command command);
    void verifyCommand(Command command);
    void acceptCommand(Command command);//TODO
    
protected:
    CommandFunction verifyCommandCallback;

    Labyrinth labyrinth;
    std::vector<Player> players;
    Player currentPlayer;//TODO pointer to a player (Player *player)
};
