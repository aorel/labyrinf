#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <boost/asio.hpp>

#include <thread>
#include <functional>

#include "events/pressedKey.h"
#include "game/gameDrawable.h"

#include "network/client_connection.h"

class Client{
public:
    Client(boost::asio::io_service& io_service,
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    ~Client();
    void run();
private:
    //int id = {0};

    //MenuDrawable menu;//TODO
    GameDrawable game;

    ClientConnection clientConnection;

    sf::RenderWindow window;
    sf::Event event;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    //sf::TcpSocket socket;


    typedef enum ClientState{
        MEMU,
        GAME,
    } ClientState;

    ClientState state = GAME;




    //std::function<void(Command)> verifyCommandCallback = std::bind( &GameDrawable::blah, game );
    //CommandFunction verifyCommandCallback;
    std::function<void(PressedKey key)> keyboardHandler;


    void events();
    void update();
    void menuKeyboardHandler(PressedKey key);
    void gameKeyboardHandler(PressedKey key);
    void render();



    //void connectionReadHandler(const Message msg);
    void connectionReadHandler(const std::string& msg);
};
