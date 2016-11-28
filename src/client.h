#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "events/pressedKey.h"
#include "game/gameDrawable.h"

class Client{
public:
    Client();
private:
    //int id = {0};

    sf::RenderWindow window;
    sf::Event event;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;


    typedef enum ClientState{
        MEMU,
        GAME,
    } ClientState;
    
    ClientState state = GAME;

    //MenuDrawable menu;//TODO
    GameDrawable game;
    
    //std::function<void(Command)> verifyCommandCallback = std::bind( &GameDrawable::blah, game );
    //CommandFunction verifyCommandCallback;
    std::function<void(PressedKey key)> keyboardHandler;

    void run();
    void events();
    void update();
    void menuKeyboardHandler(PressedKey key);
    void gameKeyboardHandler(PressedKey key);
    void render();

public:
    void commandSendTest();
    /*void commandSend(Command command);
    void commandRecv(Command command);*/
};
