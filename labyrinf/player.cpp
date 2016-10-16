#include "player.h"

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(shape);
}

Player::Player() : id(0),
                   shape(15),
                   cell_x(10),
                   cell_y(10){
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(game_settings::offset_x+cell_x*game_settings::cell_size+35.0/4.0, game_settings::offset_y+cell_y*game_settings::cell_size+35.0/4.0);
    last_step_time.restart();
}

void Player::update(sf::Time delta_time){
    //sf::Vector2f movement(0.f, 0.f);

    /*if(is_moving_up)
        movement.y -= speed;
    else if(is_moving_down)
        movement.y += speed;
    else if(is_moving_left)
        movement.x -= speed;
    else if(is_moving_right)
        movement.x += speed;
    */
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movement.y -= speed;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movement.y += speed;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= speed;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += speed;

    shape.move(movement * delta_time.asSeconds());*/
}

void Player::command(Command &command){
    if(last_step_time.getElapsedTime() > default_step_time){

        sf::Vector2f movement(0.f, 0.f);
        if(command.action == Player_up)
            movement.y -= speed;
        else if(command.action == Player_down)
            movement.y += speed;
        else if(command.action == Player_left)
            movement.x -= speed;
        else if(command.action == Player_right)
            movement.x += speed;

        shape.move(movement);
        
        last_step_time.restart();
    }
}
