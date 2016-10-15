#include "game.h"

void Game::events(){
    while (window.pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                player.handler(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                player.handler(event.key.code, false);
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time delta_time){
    player.update(delta_time);
}

void Game::render(){
    window.clear();

    labyrinth.draw(window);
    player.draw(window);

    window.display();
}




Game::Game() : window(sf::VideoMode(800, 800), "SFML works!"){
    window.setPosition(sf::Vector2i(500, 100));
}

void Game::run(){
    while (window.isOpen())
    {
        //sf::Time delta_time = clock.restart();
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
