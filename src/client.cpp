#include "client.h"
//using namespace sf;

Client::Client() : 
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),

        //[bind callback]
        //game( std::bind( &Client::commandSendTest, this ) )

        //[lambda callback]
        //game( [this](Command command){ commandSend(command); } ),
        commandHandler( [this](Command command){ playerActionHandler(command); } ){
    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
    CurrentPlay first(0, true);
    arrayPlayers.push_back(first);
    eventLoop();
}

void Client::eventLoop(){
    while (window.isOpen()){
        events();

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > settings::gameSpf){
            timeSinceLastUpdate -= settings::gameSpf;

            events();
            update();
        }

        render();
    }
}

void Client::events(){
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    while (window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if ((mouse.x >= 130) && (mouse.x <= 456) && (mouse.y >= 260) && (mouse.y <= 325)){
                    window.close();
                    Client client;
                }
                else if ((mouse.x >= 222) && (mouse.x <= 366) && (mouse.y >= 325) && (mouse.y <= 390)){
                    window.close();
                }
                break;
            default:
                break;
        }
    }
}

void Client::update(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        commandHandler(Command::PlayerUp);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        commandHandler(Command::PlayerDown);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        commandHandler(Command::PlayerLeft);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        commandHandler(Command::PlayerRight);
    }
}

void Client::menuCommandHandler(Command command){
    
}

void Client::playerActionHandler(Command command){
    //PlayerAction(&currentPlayer, command);
    game.menu();

    //Player *currentPlayer = game.getCurrentPlayer();
    
    if(game.checkPlayerAction(arrayPlayers[0].index, command) && arrayPlayers[0].isLife){
        //if(verifyСommand(server_socket, player, command))...//TODO
        arrayPlayers[0].isLife = game.applyPlayerAction(arrayPlayers[0].index, command);
    }


}

void Client::render(){
    window.clear();

    //window.draw(labyrinth);
    //window.draw(player);
    window.draw(game);

    window.display();
}

void Client::commandSend(Command command){
    //TODO
}

void Client::commandRecv(Command command){
    //TODO
}
