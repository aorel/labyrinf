#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"

class Cell : public sf::Drawable{
public:
    Cell();
    void setPosition(float x, float y);
    virtual bool isWall();
protected:
    sf::RectangleShape cell;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Wall : public Cell {
public:
    Wall();
    bool isWall();
};
