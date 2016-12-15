#include "cellDrawable.h"

//using namespace sf;

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
    if(type == HEART){
        Heart heart;
        heart.sprite.setPosition(cellShape.getPosition());
        target.draw(heart.sprite);
    }
    if(type == FIRE){
        Fire fire;
        fire.sprite.setPosition(cellShape.getPosition());
        target.draw(fire.sprite);
    }
    if(type == WATER){
        Water water;
        water.sprite.setPosition(cellShape.getPosition());
        target.draw(water.sprite);
    }
}
