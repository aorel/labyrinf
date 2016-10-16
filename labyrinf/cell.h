#pragma once

#include <SFML/Graphics.hpp>
#include "game_settings.h"

class Cell : public sf::Drawable{
private:
    sf::RectangleShape cell;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Cell();
    void setPosition(float x, float y);
};
