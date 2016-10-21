#include "gameDrawable.h"

GameDrawable::GameDrawable() :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName){
    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
}

void GameDrawable::run(){
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

void GameDrawable::events(){
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

void GameDrawable::update(sf::Time deltaTime){
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

void GameDrawable::render(){
    window.clear();

    //window.draw(labyrinth);
    window.draw(labyrinth);
    window.draw(player);

    window.display();
}

void GameDrawable::verifyCommand(Command command){
    if(player.readyForNewCommand()){
        if(labyrinth.verifyCommand(player, command)){
            //if(serverVerify(player, command))...
            player.command(command);
        }
    }
}
