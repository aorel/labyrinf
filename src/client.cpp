#include "client.h"

Client::Client() :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),

        //[bind callback]
        //game( std::bind( &Client::commandSendTest, this ) )

        //[lambda callback]
        //game( [this](Command command){ commandSend(command); } ),
        keyboardHandler( [this](PressedKey key){ gameKeyboardHandler(key); } ){
    
    sf::Socket::Status status = socket.connect("127.0.0.1", 5001);
    std::cout << "connecting...";
    if (status == sf::Socket::Done){
        std::cout << "OK" << std::endl;
    }
    else{
        std::cout << "ERROR" << std::endl;
    }
    
    
    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
    
    run();
}

void Client::run(){
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        keyboardHandler(PressedKey::Escape);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        keyboardHandler(PressedKey::Up);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        keyboardHandler(PressedKey::Down);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        keyboardHandler(PressedKey::Left);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        keyboardHandler(PressedKey::Right);
    }
}

void Client::menuKeyboardHandler(PressedKey key){
    //TODO
}

void Client::gameKeyboardHandler(PressedKey key){
    if(key == PressedKey::Escape){
        std::cout << "ECS" << std::endl;
    }
    else{
        PlayerEvent playerEvent(key);

        int currentPlayerIndex = 0;
        if(game.checkPlayerAction(currentPlayerIndex, playerEvent)){
            //if(verifyСommand(server_socket, player, command))...//TODO
            
            if(verifyCommand(playerEvent)){
                
            }
            
            game.applyPlayerAction(currentPlayerIndex, playerEvent);
        }
    }
}

void Client::render(){
    window.clear();
    window.draw(game);
    window.display();
}

bool Client::verifyCommand(const PlayerEvent& playerEvent){
    std::string data = playerEvent.generateMessage();
    
    //char bufToSend* data;
    char bufToRecv[512];
    std::size_t received;
    if(socket.send(data.c_str(), data.size()) == sf::Socket::Done){
        std::cout << "sending message: " << data << "...";
        if(socket.receive(bufToRecv, data.size(), received) == sf::Socket::Done){
            std::cout << "OK" << std::endl;
            return true;
        }
        else{
            std::cout << "RECV ERROR" << std::endl;
            return false;
        }
    }
    else{
        std::cout << "SEND ERROR" << std::endl;
        return false;
    }
}

/*void Client::commandSend(Command command){
    //TODO class Connection -> connection.sendData(event.data())
}

void Client::commandRecv(Command command){
    //TODO class Connection -> parser = connection.recvData() -> parser.callback()
}*/
