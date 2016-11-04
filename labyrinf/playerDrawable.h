#pragma once

#include <SFML/Graphics.hpp>

#include "player.h"

class PlayerDrawable : public Player, public sf::Drawable{
public:
    PlayerDrawable();

private:
    sf::CircleShape playerShape = sf::CircleShape(settings::playerRadius);
    
    void move(sf::Vector2i &movement) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
