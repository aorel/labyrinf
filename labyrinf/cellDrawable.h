#pragma once

#include <SFML/Graphics.hpp>

#include "cell.h"

class CellDrawable : public Cell, public sf::Drawable{
public:
    CellDrawable();
    void setPosition(float x, float y);
private:
    sf::RectangleShape cellShape;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
