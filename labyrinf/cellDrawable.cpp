#include "cellDrawable.h"

CellDrawable::CellDrawable() :
        cellShape(sf::Vector2f(settings::cellSize, settings::cellSize)){
}

void CellDrawable::setType(CellType t){
    type = t;
    
    switch(type){
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

void CellDrawable::setPosition(float x, float y){
    cellShape.setPosition(x, y);
}

void CellDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(cellShape, states);
}
