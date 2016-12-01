#include "client.h"

Client::Client(boost::asio::io_service& io_service,
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator) :
        //client_connection(io_service, endpoint_iterator),
        clientConnection(io_service, endpoint_iterator, std::bind(&Client::connectionReadHandler, this, std::placeholders::_1)),//, &Client::connectionReadHandler

        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),

        //[bind callback]
        //game( std::bind( &Client::commandSendTest, this ) )

        //[lambda callback]
        //game( [this](Command command){ commandSend(command); } ),
        keyboardHandler( [this](PressedKey key){ gameKeyboardHandler(key); } ){
    game.builder();

    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
    //run();

    //game._join();
}

Client::~Client(){
    clientConnection.close();
}


void Client::run(){
    while (window.isOpen()){
        events();

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > settings::gameSpf){
            timeSinceLastUpdate -= settings::gameSpf;


            events();
            //update();
            if(window.hasFocus()) update();
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
            case sf::Event::GainedFocus:
                //std::cout << "Gained" << std::endl;
                break;
            case sf::Event::LostFocus:
                //std::cout << "Lost" << std::endl;
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

            //if(verifyCommand(playerEvent)){
            //}
            std::string str = playerEvent.generateMessage();
            clientConnection.write(str);

            game.applyPlayerAction(currentPlayerIndex, playerEvent);
        }
    }
}

void Client::render(){
    window.clear();
    window.draw(game);
    window.display();
}

void Client::connectionReadHandler(const std::string& msg){
    std::cout << '[' << msg << ']' << std::endl;

}
