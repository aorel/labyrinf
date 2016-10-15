#pragma once

#include <SFML/Graphics.hpp>
#include "game_settings.h"
#include <iostream>

class Player{
private:
    int id;
    //int socket

    sf::CircleShape shape;
    float vel = 0.01;
    float vel_x = 0;
    float vel_y = 0;
    float pos_x = 10;
    float pos_y = 10;
    
    size_t cell_x;
    size_t cell_y;
    
    float speed = 500.f;
    bool is_moving_up = 0;
    bool is_moving_down = 0;
    bool is_moving_left = 0;
    bool is_moving_right = 0;

public:
    Player();
    void draw(sf::RenderWindow &window);
    void handler(sf::Keyboard::Key key, bool is_pressed);
    //void event(sf::Event &event);
    void update(sf::Time delta_time);
};
