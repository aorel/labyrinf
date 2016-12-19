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

    std::string _info();
    std::string _join();
    void _move(const int& playerIndex, const std::string& str);
    std::string _state();
    void _handler(const std::string& msg);

protected:
    Game(Labyrinth *_l);

    std::unique_ptr<Labyrinth> labyrinth;
    std::vector<std::unique_ptr<Player>> players;
    std::map<int, std::unique_ptr<Player>> testPlayers;
    int testPlayersCounter {0};

    bool isGame;
private:
    std::string _infoMsg {"_info"};
    std::string _joinMsg {"_join"};
};
