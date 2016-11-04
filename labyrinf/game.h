#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

#include "command.h"
#include "labyrinth.h"
#include "player.h"


class Game{
public:
    Game();//TODO on server side

    bool checkPlayerAction(int &playerIndex, Command &command);
    //virtual void applyPlayerAction(int &playerIndex, Command &command);
    void applyPlayerAction(int &playerIndex, Command &command);

protected:

    Game(Labyrinth *_l);
    std::unique_ptr<Labyrinth> labyrinth;
    std::vector<std::unique_ptr<Player>> players;
};
