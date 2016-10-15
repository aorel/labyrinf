#pragma once

#include <SFML/Graphics.hpp>

class Player{
private:
    int id;
    //int socket

    sf::CircleShape player;
    float vel = 0.25;
    float vel_x = 0;
    float vel_y = 0;
    float pos_x = 50;
    float pos_y = 50;

public:
    Player() : id(0){
    }
};
