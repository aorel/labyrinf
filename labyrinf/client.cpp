#include "client.h"

Client::Client() :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),

        //[bind callback]
        //game( std::bind( &Client::commandSendTest, this ) )

        //[lambda callback]
        //game( [this](Command command){ commandSend(command); } ),
        commandHandler( [this](Command command){ gameCommandHandler(command); } ){
    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
    
    //game.run();
    eventLoop();
}

/*
void Client::run(){
    game.run();
}
*/

void Client::eventLoop(){
    while (window.isOpen()){
        events();

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > settings::gameSpf){
            timeSinceLastUpdate -= settings::gameSpf;

            events();
            update();//TODO settings::gameSpf
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

void Client::gameCommandHandler(Command command){
    if(game.checkCommand(command)){
        //if(verifyСommand(server_socket, player, command)){//TODO
        //}
        game.applyCommand(command);
    }

    /*if(player.readyForNewCommand()){
        if(labyrinth.verifyCommand(player, command)){
            //if(serverVerify(player, command))...
            player.command(command);
        }
    }*/
}

void Client::render(){
    window.clear();

    //window.draw(labyrinth);
    //window.draw(player);
    window.draw(game);

    window.display();
}

void Client::commandSendTest(){
    std::cout << "commandSendTest" << std::endl;
}

void Client::commandSend(Command command){

}
void Client::commandRecv(Command command){

}
