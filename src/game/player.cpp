#include "player.h"

Player::Player() :
        position(settings::playerStartPositionX, settings::playerStartPositionY){
    lastStepTime.restart();
    std::cout << "Player" << std::endl;
}

bool Player::readyForNewCommand(){
    if(lastStepTime.getElapsedTime() > settings::playerSpf){
        return true;
    }
    else{
        return false;
    }
}

void Player::applyCommand(const PlayerEvent& playerEvent){
    sf::Vector2i movement(0, 0);

    PressedKey key = playerEvent.getKey();
    if(key == PressedKey::Up)
        movement.y -= 1;
    else if(key == PressedKey::Down)
        movement.y += 1;
    else if(key == PressedKey::Left)
        movement.x -= 1;
    else if(key == PressedKey::Right)
        movement.x += 1;

    this->move(movement);

    lastStepTime.restart();
}

void Player::setPosition(const int& x, const int& y){
    int dx = x-position.x;
    int dy = y-position.y;
    std::cout << position.x << "_" << position.y << std::endl;
    std::cout << dx << "_" << dy << std::endl;

    sf::Vector2i movement(dx, dy);
    this->move(movement);

    lastStepTime.restart();
}

sf::Vector2i Player::getPosition() const{
    return position;
}

std::string Player::getPositionInString() const{
    sf::Vector2i position = getPosition();

    std::string returnString(std::to_string(position.x));
    returnString.append(",");
    returnString.append(std::to_string(position.y));
    return returnString;
}

void Player::move(sf::Vector2i movement){
    position += movement;
    std::cout << "Player::move " << position.x << ' ' << position.y << std::endl;
}
