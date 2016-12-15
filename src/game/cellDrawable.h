#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "cell.h"
#include "bonuses.h"
#include "../settingsDrawable.h"

class CellDrawable : public Cell, public sf::Drawable{
public:
    CellDrawable();
    void setType(CellType t) override;
    void setPosition(float x, float y);

private:
    sf::RectangleShape cellShape;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
