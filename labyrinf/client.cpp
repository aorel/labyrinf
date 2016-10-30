#include "client.h"

Client::Client() :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),

        //[bind callback]
        //game( std::bind( &Client::commandSendTest, this ) )

        //[lambda callback]
        game( [this](Command command){ commandSend(command); } ){
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
        //verifyCommand(Command::PlayerUp);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        //verifyCommand(Command::PlayerDown);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        //verifyCommand(Command::PlayerLeft);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        //verifyCommand(Command::PlayerRight);
    }
}

void Client::commandHandler(Command command){
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
