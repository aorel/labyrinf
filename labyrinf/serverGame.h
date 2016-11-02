#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

//#include "abstractGame.h"
#include "command.h"
#include "labyrinth.h"
#include "player.h"


class ServerGame{
public:
    ServerGame() = default;//TODO on server side

    bool checkPlayerAction(int &playerIndex, Command &command);
    virtual void applyPlayerAction(int &playerIndex, Command &command);

protected:
    Labyrinth labyrinth;
    std::vector<Player> players;
};
