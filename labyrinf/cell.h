#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"

class Cell : public sf::Drawable{
public:
    Cell();
    void setPosition(float x, float y);
private:
    sf::RectangleShape cell;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
