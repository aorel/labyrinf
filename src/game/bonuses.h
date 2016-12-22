#pragma once

#include "../settingsDrawable.h"

class AbstractBonuse{
public:
    sf::Sprite sprite;
protected:
    sf::Image image;
    sf::Texture texture;
};

class Heart : public AbstractBonuse{
public:
    //sf::Sprite sprite;
    Heart(){
        image.loadFromFile(settingsDrawable::imgPathHeart);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setScale(settingsDrawable::imgScaleHeart);
    }
private:
    //sf::Image image;
    //sf::Texture texture;
};

class Fire : public AbstractBonuse{
public:
    //sf::Sprite sprite;
    Fire(){
        image.loadFromFile(settingsDrawable::imgPathFire);
        image.createMaskFromColor(settingsDrawable::imgMaskColorFire);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setScale(settingsDrawable::imgScaleFire);
    }
private:
    //sf::Image image;
    //sf::Texture texture;
};

class Water : public AbstractBonuse{
public:
    //sf::Sprite sprite;
    Water(){
        image.loadFromFile(settingsDrawable::imgPathWater);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, settingsDrawable::cellDrawableSize, settingsDrawable::cellDrawableSize));
    }
private:
    //sf::Image image;
    //sf::Texture texture;
};

