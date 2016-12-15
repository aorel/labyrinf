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

<<<<<<< HEAD
class Heart
{
    Image image;
    Texture texture;
public:
    Sprite sprite;
    Heart()
    {
        image.loadFromFile("//home//frozenfoot//Desktop//TechnoPark//C++//git//labyrinf//src//game//heart.png");
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
        image.loadFromFile("//home//frozenfoot//Desktop//TechnoPark//C++//git//labyrinf//src//game//fire.jpg");
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
        image.loadFromFile("//home//frozenfoot//Desktop//TechnoPark//C++//git//labyrinf//src//game//water.jpg");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, settings::cellSize, settings::cellSize));
    }
};

=======
>>>>>>> develop
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
