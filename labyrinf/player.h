#pragma once

#include <SFML/Graphics.hpp>
#include "command.h"
#include "game_settings.h"

class Player : public sf::Drawable{
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

    sf::Clock last_step_time;
    sf::Time default_step_time = sf::seconds(1.f/10.f);

    float speed = 50.f;
    bool is_moving_up = 0;
    bool is_moving_down = 0;
    bool is_moving_left = 0;
    bool is_moving_right = 0;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Player();
    void update(sf::Time delta_time);
    void command(Command &c);
};
