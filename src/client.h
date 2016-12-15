#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include <boost/asio.hpp>
#include <thread>
#include <functional>

#include "events/pressedKey.h"
#include "game/gameDrawable.h"

//<<<<<<< HEAD
#include "network/client_connection.h"
//=======
struct CurrentPlay
{
    int index;
    bool isLife;
    CurrentPlay(int _index = 0, bool _isLife = 1) : index(_index), isLife(_isLife) {}
};
//>>>>>>> feature/game

class Client{
public:
    Client();
    Client(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    Client(boost::asio::io_service& io_service,
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    ~Client();
    void run();
private:
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

//<<<<<<< HEAD

//=======
    //std::function< void(Command command) > commandHandler;
    
    std::vector<CurrentPlay> arrayPlayers;
//>>>>>>> feature/game


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
