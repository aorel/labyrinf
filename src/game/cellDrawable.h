#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

#include "cell.h"
#include <iostream>

class CellDrawable : public Cell, public sf::Drawable{
public:
    CellDrawable();
    
    virtual void setType(CellType t) override;
    
    void setPosition(float x, float y);
private:
    sf::RectangleShape cellShape;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
