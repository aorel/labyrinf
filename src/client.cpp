#include "client.h"

Client::Client() :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),
        keyboardHandler( [this](PressedKey key){ gameKeyboardHandler(key); } ),
        sendToServer( [this](const PlayerEvent& playerEvent){ virtualConnectionWrite(playerEvent); } ){
    game.init();
    window.setPosition(sf::Vector2i(settings::windowPositionX, settings::windowPositionY));
}

Client::Client(boost::asio::io_service& ioService,
    boost::asio::ip::tcp::resolver::iterator endpointIterator) :
        window(sf::VideoMode(settings::windowSizeX, settings::windowSizeY), settings::windowName),
        keyboardHandler( [this](PressedKey key){ gameKeyboardHandler(key); } ),
        sendToServer( [this](const PlayerEvent& playerEvent){ connectionWrite(playerEvent); } ){
    game.init();

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
        if(game.checkPlayerAction(currentPlayerIndex, playerEvent)){
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
    game.applyPlayerAction(currentPlayerIndex, playerEvent);
}

void Client::connectionReadHandler(const std::string& msg){
    std::cout << '[' << msg << ']' << std::endl;

    size_t start(msg.find_first_of('@'));
    size_t end(0);
    int i(0);
    while(1){
        end = msg.find_first_of('@', start+1);

        if(end == std::string::npos){
            break;
        }

        std::cout << '!' << msg.substr(start, end) << std::endl;


        size_t i1pos = msg.find_first_of(':', start);
        size_t i2pos = msg.find_first_of(',', start);
        std::cout << '^' << msg.substr(i1pos+1, end) << std::endl;
        std::cout << '^' << msg.substr(i2pos+1, end) << std::endl;
        int i1 = std::stoi(msg.substr(i1pos+1, end));
        int i2 = std::stoi(msg.substr(i2pos+1, end));
        std::cout << '?' << i1 << "-" << i2 << std::endl;
            game.setPlayerPosition(i, i1, i2);

        start = end;
        ++i;
    }
    end = msg.find_first_of('\n', start+1);
    std::cout << '!' << msg.substr(start, end) << std::endl;

        size_t i1pos = msg.find_first_of(':', start);
        size_t i2pos = msg.find_first_of(',', start);
        std::cout << '^' << msg.substr(i1pos+1, end) << std::endl;
        std::cout << '^' << msg.substr(i2pos+1, end) << std::endl;
        int i1 = std::stoi(msg.substr(i1pos+1, end));
        int i2 = std::stoi(msg.substr(i2pos+1, end));
        std::cout << '?' << i1 << "-" << i2 << std::endl;
            game.setPlayerPosition(i, i1, i2);
}
