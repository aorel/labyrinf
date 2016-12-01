#include "playerDrawable.h"

PlayerDrawable::PlayerDrawable(){
    playerShape.setFillColor(settings::playerDrawableColor);
    playerShape.setPosition(
        settings::playerDrawableOffsetX + position.x * settings::cellDrawableSize,
        settings::playerDrawableOffsetY + position.y * settings::cellDrawableSize
    );
}

void PlayerDrawable::move(sf::Vector2i &movement){
    Player::move(movement);
    playerShape.move(
        movement.x * settings::cellDrawableSize,
        movement.y * settings::cellDrawableSize
    );
}

void PlayerDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(playerShape, states);
}
