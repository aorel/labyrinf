#include "playerDrawer.h"

PlayerDrawer::PlayerDrawer(const Player *p) :
        player(p),
        playerShape(settings::playerRadius){
    playerShape.setFillColor(sf::Color::Red);
    
    updatePosition();
}

void PlayerDrawer::updatePosition(){
    setPosition(player->getPosition());
}

void PlayerDrawer::setPosition(const sf::Vector2i &position){
    playerShape.setPosition(settings::playerOffsetX + position.x * settings::cellSize, settings::playerOffsetY + position.y * settings::cellSize);
}

void PlayerDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(playerShape, states);
}
