#pragma once

#include <SFML/Graphics.hpp>

#include "cell.h"

class CellDrawer : public sf::Drawable{
public:
    explicit CellDrawer(const Cell *c);
    void setPosition(float x, float y);
    void updateType();
private:
    const Cell *cell;
    sf::RectangleShape cellShape;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
