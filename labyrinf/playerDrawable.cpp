#include "playerDrawable.h"

PlayerDrawable::PlayerDrawable() : playerShape(settings::playerRadius){
    playerShape.setFillColor(sf::Color::Red);
    playerShape.setPosition(settings::playerOffsetX + position.x * settings::cellSize, settings::playerOffsetY + position.y * settings::cellSize);
}

void PlayerDrawable::move(sf::Vector2i &movement){
    Player::move(movement);
    playerShape.move(movement.x * settings::cellSize, movement.y * settings::cellSize);
}

void PlayerDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(playerShape, states);
}
