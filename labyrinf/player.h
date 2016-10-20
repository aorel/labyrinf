#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "command.h"
#include "settings.h"

class Player : public sf::Drawable{
public:
    Player();
    void command(Command &command);
    sf::Vector2i getPosition();

private:
    int id = {0};
    //int socket

    sf::CircleShape shape;//??? sf::CircleShape shape = {sf::CircleShape(settings::playerRadius)}
    sf::Vector2i position;

    sf::Clock lastStepTime;
    //sf:Time time_per_frame = sf::seconds(1.f/7.f);

    void move(sf::Vector2i &movement);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
