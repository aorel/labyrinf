#include "client.h"

Client::Client() :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),
        keyboardHandler( [this](PressedKey key){ gameKeyboardHandler(key); } ),
        sendToServer( [this](const PlayerEvent& playerEvent){ virtualConnectionWrite(playerEvent); } ){
    std::cout << "Client local" << std::endl;

    game.addLocalPlayer();
    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
}

Client::Client(boost::asio::io_service& ioService,
    boost::asio::ip::tcp::resolver::iterator endpointIterator) :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),
        keyboardHandler( [this](PressedKey key){ gameKeyboardHandler(key); } ),
        sendToServer( [this](const PlayerEvent& playerEvent){ connectionWrite(playerEvent); } ){
    std::cout << "Client multiplayer" << std::endl;
    //game.init();

    clientConnection = std::make_shared<ClientConnection>(
        ioService,
        endpointIterator,
        std::bind(&Client::connectionReadHandler, this, std::placeholders::_1)
    );

    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
}

Client::~Client(){
    if(clientConnection){
        clientConnection->close();
    }
}

void Client::run(){
    while (window.isOpen()){
        events();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > settings::gameSpf){
            timeSinceLastUpdate -= settings::gameSpf;
            events();
            if(window.hasFocus()) update();
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
            case sf::Event::GainedFocus:
                break;
            case sf::Event::LostFocus:
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
        if(game.checkPlayerAction(playerEvent)){
            sendToServer(playerEvent);
        }
    }
}

void Client::render(){
    window.clear();
    window.draw(game);
    window.display();
}

void Client::connectionWrite(const PlayerEvent& playerEvent){
    std::string str = playerEvent.generateMessage();
    std::cout << str << std::endl;
    clientConnection->write(str);
}

void Client::virtualConnectionWrite(const PlayerEvent& playerEvent){
    game.applyPlayerAction(playerEvent);
}

void Client::connectionReadHandler(const std::string& msg){
    std::cout << '[' << msg << ']' << std::endl;
    game._handler(msg);
}
