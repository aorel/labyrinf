#include "player.h"

void Player::move(sf::Vector2i &movement){
    position += movement;
    shape.move(movement.x * settings::cell_size, movement.y * settings::cell_size);
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(shape);
}

Player::Player() : id(0),
                   shape(settings::player_radius),
                   position(10, 10){
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(settings::player_offset_x + position.x * settings::cell_size, settings::player_offset_y + position.y * settings::cell_size);
    last_step_time.restart();//pos_y*settings::cell_size+
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

        /*sf::Vector2f movement(0.f, 0.f);
        if(command.action == Player_up)
            movement.y -= settings::cell_size;
        else if(command.action == Player_down)
            movement.y += settings::cell_size;
        else if(command.action == Player_left)
            movement.x -= settings::cell_size;
        else if(command.action == Player_right)
            movement.x += settings::cell_size;

        shape.move(movement);*/
        sf::Vector2i movement(0, 0);
        if(command.action == Player_up)
            movement.y -= 1;
        else if(command.action == Player_down)
            movement.y += 1;
        else if(command.action == Player_left)
            movement.x -= 1;
        else if(command.action == Player_right)
            movement.x += 1;

        move(movement);
        //shape.move(movement);
        
        last_step_time.restart();
    }
}

sf::Vector2i Player::get_position(){
    return position;
}
