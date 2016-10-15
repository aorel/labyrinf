#include "player.h"

Player::Player() : id(0),
                   shape(15),
                   cell_x(10),
                   cell_y(10){
    shape.setFillColor(sf::Color::Red);
}

void Player::draw(sf::RenderWindow &window){
    //shape.setPosition(game_settings::offset_x+cell_x*game_settings::cell_size+35.0/4.0, game_settings::offset_y+cell_y*game_settings::cell_size+35.0/4.0);
    window.draw(shape);
}

void Player::handler(sf::Keyboard::Key key, bool is_pressed){
    if(key == sf::Keyboard::Up)
        is_moving_up = is_pressed;
    else if(key == sf::Keyboard::Down)
        is_moving_down = is_pressed;
    else if(key == sf::Keyboard::Left)
        is_moving_left = is_pressed;
    else if(key == sf::Keyboard::Right)
        is_moving_right = is_pressed;
}

void Player::update(sf::Time delta_time){
    sf::Vector2f movement(0.f, 0.f);
    if(is_moving_up)
        movement.y -= speed;
    else if(is_moving_down)
        movement.y += speed;
    else if(is_moving_left)
        movement.x -= speed;
    else if(is_moving_right)
        movement.x += speed;
        
    shape.move(movement * delta_time.asSeconds());
}
