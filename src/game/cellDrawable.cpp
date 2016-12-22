#include "cellDrawable.h"

CellDrawable::CellDrawable() :
        cellShape(sf::Vector2f(settingsDrawable::cellDrawableSize, settingsDrawable::cellDrawableSize)){
}

void CellDrawable::setType(CellType t){
    type = t;

    switch(type){
        case WALL:
            cellShape.setFillColor(settingsDrawable::cellDrawableTypeWall);
            break;
        case GROUND:
            cellShape.setFillColor(settingsDrawable::cellDrawableTypeGround);
            break;
        case WATER:
            cellShape.setFillColor(settingsDrawable::cellDrawableTypeWater);
            break;
        case FIRE:
            cellShape.setFillColor(settingsDrawable::cellDrawableTypeFire);
            break;
        case HEART:
            cellShape.setFillColor(settingsDrawable::cellDrawableTypeGround);
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
    
    AbstractBonuse* bonuse(0);
    if(type == HEART){
        bonuse = new Heart;
    }
    if(type == FIRE){
        bonuse = new Fire;
    }
    if(type == WATER){
        bonuse = new Water;
    }
    if(bonuse!=0){
        bonuse->sprite.setPosition(cellShape.getPosition());
        target.draw(bonuse->sprite);
    }
    delete bonuse;
}
