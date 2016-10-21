#include "game.h"

Game::Game() :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName){
        //labyrinthDrawer(&labyrinth){
        //playerDrawer(&player){
    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
}

void Game::run(){
    while (window.isOpen())
    {
        events();

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > settings::gameSpf){
            timeSinceLastUpdate -= settings::gameSpf;

            events();
            update(settings::gameSpf);
        }

        render();
    }
}

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

void Game::update(sf::Time deltaTime){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        verifyCommand(Command::PlayerUp);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        verifyCommand(Command::PlayerDown);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        verifyCommand(Command::PlayerLeft);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        verifyCommand(Command::PlayerRight);
    }
}

void Game::render(){
    window.clear();

    //window.draw(labyrinth);
    window.draw(labyrinth);
    window.draw(player);

    window.display();
}

void Game::verifyCommand(Command command){
    if(player.readyForNewCommand()){
        if(labyrinth.verifyCommand(player, command)){
            //if(serverVerify(player, command))...
            player.command(command);
        }
    }
}
