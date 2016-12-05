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
    Client();
    Client(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    Client(boost::asio::io_service& io_service,
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    ~Client();
    void run();
private:
    //int id = {0};

    //MenuDrawable menu;//TODO
    GameDrawable game;

    std::shared_ptr<ClientConnection> clientConnection;

    sf::RenderWindow window;
    sf::Event event;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    typedef enum ClientState{
        MEMU,
        GAME,
    } ClientState;

    ClientState state = GAME;




    std::function<void(PressedKey key)> keyboardHandler;


    void events();
    void update();
    void menuKeyboardHandler(PressedKey key);
    void gameKeyboardHandler(PressedKey key);
    void render();

    const int currentPlayerIndex = 0;
    std::function<void(const PlayerEvent&)> sendToServer;
    void connectionWrite(const PlayerEvent&);
    void virtualConnectionWrite(const PlayerEvent&);

    //void connectionReadHandler(const Message msg);
    void connectionReadHandler(const std::string& msg);
};
