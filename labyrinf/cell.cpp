#include "cell.h"

Cell::Cell() : cell(sf::Vector2f(settings::cellSize, settings::cellSize)){
    cell.setFillColor(sf::Color(50, 50, 50));
    cell.setOutlineThickness(2);
    cell.setOutlineColor(sf::Color(150, 150, 150));
}

void Cell::setPosition(float x, float y){
    cell.setPosition(x, y);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(cell, states);
}
