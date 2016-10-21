#include "cellDrawable.h"

CellDrawable::CellDrawable() : cellShape(sf::Vector2f(settings::cellSize, settings::cellSize)){
    cellShape.setFillColor(sf::Color(50, 50, 50));
    cellShape.setOutlineThickness(2);
    cellShape.setOutlineColor(sf::Color(150, 150, 150));
}

void CellDrawable::setPosition(float x, float y){
    cellShape.setPosition(x, y);
}

void CellDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(cellShape, states);
}
