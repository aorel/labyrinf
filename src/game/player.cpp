#include "player.h"

Player::Player() :
        position(settings::playerStartPositionX, settings::playerStartPositionY){
    lastStepTime.restart();
    health = 2;
    wet = 0;
}

bool Player::readyForNewCommand(){
    if(lastStepTime.getElapsedTime() > settings::playerSpf){
        return true;
    }
    else{
        return false;
    }
}

void Player::applyCommand(Command &command){
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

    lastStepTime.restart();
}

sf::Vector2i Player::getPosition() const{
    return position;
}

void Player::move(sf::Vector2i &movement){
    position += movement;
    std::cout << "Player::move " << position.x << ' ' << position.y << std::endl;
}

void Player::addHealth(int add)
{
    health += add;
}
int Player::getHealth() const
{
    return health;
}

void Player::changeWet()
{
    wet = !wet;
}

bool Player::isWet() const
{
    return wet;
}
