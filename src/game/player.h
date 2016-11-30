#pragma once

#include <iostream>

#include "../command.h"
#include "../settings.h"
#include "cellDrawable.h"
#include "labyrinth.h"

class Player{
public:
    Player();
    virtual ~Player() = default;

    bool readyForNewCommand();
    void applyCommand(Command &command);
    sf::Vector2i getPosition() const;

protected:
    sf::Clock lastStepTime;
    
    //int socket = {0};
    //int id = {0};
    sf::Vector2i position;
    int health;
    bool isWet;//TODO bonus, health, etc
    
    virtual void move(sf::Vector2i &movement);
};


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
