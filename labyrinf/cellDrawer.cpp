#include "cellDrawer.h"

CellDrawer::CellDrawer(const Cell *c) :
        cell(c),
        cellShape(sf::Vector2f(settings::cellSize, settings::cellSize)){
    //cellShape.setFillColor(sf::Color(50, 50, 50));
    //cellShape.setOutlineThickness(settings::cellOutlineThickness);
    //cellShape.setOutlineColor(sf::Color(150, 150, 150));
    updateType();
}

void CellDrawer::setPosition(float x, float y){
    cellShape.setPosition(x, y);
}
void CellDrawer::updateType(){
    CellType t = cell->getType();
    switch(t){
        case WALL:
            cellShape.setFillColor(settings::cellTypeWall);
            break;
        case GROUND:
            cellShape.setFillColor(settings::cellTypeGround);
            break;
        case WATER:
            cellShape.setFillColor(settings::cellTypeWater);
            break;
        case FIRE:
            cellShape.setFillColor(settings::cellTypeFire);
            break;
        default:
            break;
    }
}

void CellDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(cellShape, states);
}
