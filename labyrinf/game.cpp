#include "game.h"

void Game::events(){
    while (window.pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time delta_time){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        verify_action(Action::Player_up);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        verify_action(Action::Player_down);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        verify_action(Action::Player_left);
    }
        
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        verify_action(Action::Player_right);
    }



    player.update(delta_time);
}

void Game::render(){
    window.clear();

    window.draw(labyrinth);
    window.draw(player);

    window.display();
}

void Game::verify_action(Action action){
    Command c(action);
    if(labyrinth.verify_command(player, c, time_per_frame))
        player.command(c);
        
}

Game::Game() : window(sf::VideoMode(800, 800), "SFML works!"){
    window.setPosition(sf::Vector2i(500, 100));
}

void Game::run(){
    while (window.isOpen())
    {
        events();
        
        time_since_last_update += clock.restart();
        while (time_since_last_update > time_per_frame){
            time_since_last_update -= time_per_frame;
            
            events();
            update(time_per_frame);
        }
        render();
    }
}
