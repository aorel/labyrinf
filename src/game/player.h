#pragma once

#include <iostream>

//#include "../command.h"
#include "../events/playerEvent.h"
#include "../settings.h"

class Player{
public:
    Player();
    virtual ~Player() = default;

    bool readyForNewCommand();
    void applyCommand(const PlayerEvent&);
    sf::Vector2i getPosition() const;
    std::string getPositionInString() const;

protected:
    sf::Clock lastStepTime;

    //int socket = {0};
    //int id = {0};
    sf::Vector2i position;
    int state = {0};//TODO bonus, health, etc

    virtual void move(sf::Vector2i &movement);
};

/*
class PlayerAction{
public:
    PlayerAction(Player *p, Command c) : player(p), command(c){}
    Player* getPlayer(){
        return player;
    }
private:
    Player *player;
    Command command;
};
*/
