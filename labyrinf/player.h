#pragma once

#include <iostream>

#include "command.h"
#include "settings.h"

class Player{
public:
    Player();
    bool readyForNewCommand();
    void applyCommand(Command &command);
    sf::Vector2i getPosition() const;

protected:
    //int socket = {0};
    //int id = {0};
    sf::Vector2i position;
    int state = {0};//TODO bonus, health, etc
    
    virtual void move(sf::Vector2i &movement);

private:
    sf::Clock lastStepTime;
};
