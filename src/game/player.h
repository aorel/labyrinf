#pragma once

#include <iostream>

#include "../events/playerEvent.h"
#include "../settings.h"

class Player{
public:
    Player();
    virtual ~Player() = default;

    bool readyForNewCommand();
    void applyCommand(const PlayerEvent&);
    void setPosition(const int& x, const int& y);
    sf::Vector2i getPosition() const;
    std::string getPositionInString() const;

protected:
    sf::Clock lastStepTime;

    sf::Vector2i position;
    int state = {0};//TODO bonus, health, etc

    virtual void move(sf::Vector2i movement);
};
