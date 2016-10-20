#include "player.h"

Player::Player() : shape(settings::playerRadius),
                   position(settings::playerStartPositionX, settings::playerStartPositionY){
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(settings::playerOffsetX + position.x * settings::cellSize, settings::playerOffsetY + position.y * settings::cellSize);
    lastStepTime.restart();
}

bool Player::readyForNewCommand(){
    if(lastStepTime.getElapsedTime() > settings::playerSpf){
        return true;
    }
    else{
        return false;
    }
}

void Player::command(Command &command){
    //if(lastStepTime.getElapsedTime() > settings::playerSpf){

    sf::Vector2i movement(0, 0);
    if(command == PlayerUp)
        movement.y -= 1;
    else if(command == PlayerDown)
        movement.y += 1;
    else if(command == PlayerLeft)
        movement.x -= 1;
    else if(command == PlayerRight)
        movement.x += 1;

    move(movement);
    //shape.move(movement);
        
    lastStepTime.restart();
    //}
}

sf::Vector2i Player::getPosition(){
    return position;
}

void Player::move(sf::Vector2i &movement){
    position += movement;
    shape.move(movement.x * settings::cellSize, movement.y * settings::cellSize);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(shape);
}
