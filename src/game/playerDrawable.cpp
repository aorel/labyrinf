#include "playerDrawable.h"

PlayerDrawable::PlayerDrawable(){
    position.x = 1;
    position.y = 1;


    playerShape.setFillColor(settingsDrawable::playerDrawableColor);
    playerShape.setPosition(
        settingsDrawable::playerDrawableOffsetX + position.x * settingsDrawable::cellDrawableSize,
        settingsDrawable::playerDrawableOffsetY + position.y * settingsDrawable::cellDrawableSize
    );
}

void PlayerDrawable::move(sf::Vector2i& movement){
    Player::move(movement);
    playerShape.move(
        movement.x * settingsDrawable::cellDrawableSize,
        movement.y * settingsDrawable::cellDrawableSize
    );
}

void PlayerDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(playerShape, states);
}
