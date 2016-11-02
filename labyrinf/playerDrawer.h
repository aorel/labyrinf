#pragma once

#include <SFML/Graphics.hpp>

#include "settings.h"
#include "player.h"

class PlayerDrawer : public sf::Drawable{
public:
    explicit PlayerDrawer(const Player *p);
    void updatePosition();

private:
    const Player *player;
    sf::CircleShape playerShape;

    void setPosition(const sf::Vector2i &position);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
