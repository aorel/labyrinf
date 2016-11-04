#include "client.h"

Client::Client() :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),

        //[bind callback]
        //game( std::bind( &Client::commandSendTest, this ) )

        //[lambda callback]
        //game( [this](Command command){ commandSend(command); } ),
        commandHandler( [this](Command command){ playerActionHandler(command); } ){
    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
    
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
    while (window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
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
    //TODO
}

void Client::playerActionHandler(Command command){
    //PlayerAction(&currentPlayer, command);


    //Player *currentPlayer = game.getCurrentPlayer();
    int currentPlayerIndex = 0;
    if(game.checkPlayerAction(currentPlayerIndex, command)){
        //if(verifyСommand(server_socket, player, command))...//TODO
        game.applyPlayerAction(currentPlayerIndex, command);
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
