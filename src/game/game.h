#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

#include "../events/playerEvent.h"
#include "labyrinth.h"
#include "player.h"

class Game{
public:
    Game();
    virtual void init();

    bool checkPlayerAction(const int& playerIndex, const PlayerEvent& playerEvent);
    void applyPlayerAction(const int& playerIndex, const PlayerEvent& playerEvent);
    void setPlayerPosition(const int& playerIndex, const int& x, const int& y);
    void isGameTest();

    void _join();
    void _move(const int& playerIndex, const std::string& str);
    std::string _state();

protected:
    Game(Labyrinth *_l);

    std::unique_ptr<Labyrinth> labyrinth;
    std::vector<std::unique_ptr<Player>> players;
    bool isGame;
};
