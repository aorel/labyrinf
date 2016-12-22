#include "player.h"

Player::Player() :
        position(settings::playerStartPositionX, settings::playerStartPositionY){
    lastStepTime.restart();
    std::cout << "Player()" << std::endl;
    health = 2;
    wet = 0;
}

bool Player::readyForNewCommand(){
    return lastStepTime.getElapsedTime() > settings::playerSpf;
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

    move(movement);
    lastStepTime.restart();
}

void Player::setPosition(const int& x, const int& y){
    int dx = x-position.x;
    int dy = y-position.y;
    std::cout << position.x << "_" << position.y << std::endl;
    std::cout << dx << "_" << dy << std::endl;

    sf::Vector2i movement(dx, dy);
    move(movement);
    lastStepTime.restart();
}

sf::Vector2i Player::getPosition() const{
    return position;
}

std::string Player::positionToString() const{
    sf::Vector2i position = getPosition();

    std::string returnString(std::to_string(position.x));
    returnString.append(",");
    returnString.append(std::to_string(position.y));
    return returnString;
}
void Player::positionFromString(const std::string& str){
    //TODO
}

void Player::move(sf::Vector2i& movement){
    position += movement;
    std::cout << "Player::move " << position.x << ' ' << position.y << std::endl;
}

void Player::addHealth(int add){
    health += add;
}

int Player::getHealth() const{
    return health;
}

void Player::changeWet(){
    wet = !wet;
}

bool Player::isWet() const{
    return wet;
}
