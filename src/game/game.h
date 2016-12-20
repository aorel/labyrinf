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
    virtual void addLocalPlayer();
    virtual void addPlayer(const int& playerIndex);
    void delPlayer(const int& playerIndex);

    bool checkPlayerAction(const PlayerEvent& playerEvent);
    bool checkPlayerAction(const int& playerIndex, const PlayerEvent& playerEvent);
    void applyPlayerAction(const PlayerEvent& playerEvent);
    void applyPlayerAction(const int& playerIndex, const PlayerEvent& playerEvent);
    void setPlayerPosition(const int& playerIndex, const int& x, const int& y);
    void afterPlayerAction(const int& playerIndex);
    void isGameTest();

    void debugPrint();
    std::string _info();
    int _joinKey();
    std::string _join();
    std::string _add();
    std::string _del(const int& playerIndex);
    std::string _move(const int& playerIndex, const std::string& str);
    std::string _state();
    void _handler(const std::string& msg);
    bool _parser(const std::string& msg, size_t& startPos, size_t& endPos, int& key);
    bool _parser(const std::string& msg, size_t& startPos, size_t& endPos, int& key, int& x, int& y);

protected:
    Game(Labyrinth *_l);

    std::unique_ptr<Labyrinth> labyrinth;
    //std::vector<std::unique_ptr<Player>> players;
    std::map<int, std::unique_ptr<Player>> players;
    int playersCounter {0};
    int localPlayer {0};

    bool isGame;
private:
    //std::string _infoMsg {"_info"};
    //std::string _joinMsg {"_join"};
    //std::string _moveMsg {"_move"};
};
