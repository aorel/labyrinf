#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

//#include "../command.h"
#include "../events/playerEvent.h"
#include "labyrinth.h"
#include "player.h"


class Game{
public:
    Game();
    virtual void builder();

    bool checkPlayerAction(int &, const PlayerEvent&);
    //virtual void applyPlayerAction(int &playerIndex, Command &command);
    void applyPlayerAction(int &playerIndex, const PlayerEvent&);


    void _join();
    void _move(const int& playerIndex, const std::string& str);
    std::string _state();

protected:
    virtual std::unique_ptr<Labyrinth> labyrinthBuilder();
    virtual std::unique_ptr<Player> playerBuilder();

    std::unique_ptr<Labyrinth> labyrinth;
    std::vector<std::unique_ptr<Player>> players;
};
