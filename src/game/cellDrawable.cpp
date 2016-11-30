#include "cellDrawable.h"

using namespace sf;

CellDrawable::CellDrawable() :
        cellShape(Vector2f(settings::cellSize, settings::cellSize)){
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
        case HEART:
            cellShape.setFillColor(settings::cellTypeGround);
            break;
        default:
            break;
    }
}

void CellDrawable::setPosition(float x, float y){
    cellShape.setPosition(x, y);
}

class Heart
{
    Image image;
    Texture texture;
public:
    Sprite sprite;
    Heart()
    {
        image.loadFromFile("/home/ivyazmin/park/labyrinf_new/labyrinf/src/heart.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setScale(Vector2f(0.4f, 0.4f));
    }
};

class Fire
{
    Image image;
    Texture texture;
public:
    Sprite sprite;
    Fire()
    {
        image.loadFromFile("/home/ivyazmin/park/labyrinf_new/labyrinf/src/fire.jpg");
        image.createMaskFromColor(Color(255,255,255));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setScale(Vector2f(0.12f, 0.12f));
    }
};

class Water
{
    Image image;
    Texture texture;
public:
    Sprite sprite;
    Water()
    {
        image.loadFromFile("/home/ivyazmin/park/labyrinf_new/labyrinf/src/water.jpg");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, settings::cellSize, settings::cellSize));
    }
};

void CellDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(cellShape, states);
    if (getType() == HEART){
        Heart heart;
        heart.sprite.setPosition(cellShape.getPosition());
        target.draw(heart.sprite);
    }
    if (getType() == FIRE){
        Fire fire;
        fire.sprite.setPosition(cellShape.getPosition());
        target.draw(fire.sprite);
    }
    if (getType() == WATER){
        Water water;
        water.sprite.setPosition(cellShape.getPosition());
        target.draw(water.sprite);
    }
}

