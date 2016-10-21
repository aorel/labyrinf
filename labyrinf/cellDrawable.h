#pragma once

#include <SFML/Graphics.hpp>

#include "cell.h"

class CellDrawable : public Cell, public sf::Drawable{
public:
    CellDrawable();
    void setPosition(float x, float y);
private:
    sf::RectangleShape cellShape;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
