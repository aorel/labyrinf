#include "cellDrawable.h"

CellDrawable::CellDrawable() :
        cellShape(sf::Vector2f(settings::cellDrawableSize, settings::cellDrawableSize)){
}

void CellDrawable::setType(CellType t){
    type = t;

    switch(type){
        case WALL:
            cellShape.setFillColor(settings::cellDrawableTypeWall);
            break;
        case GROUND:
            cellShape.setFillColor(settings::cellDrawableTypeGround);
            break;
        case WATER:
            cellShape.setFillColor(settings::cellDrawableTypeWater);
            break;
        case FIRE:
            cellShape.setFillColor(settings::cellDrawableTypeFire);
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
