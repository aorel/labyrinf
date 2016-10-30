#pragma once

#include <SFML/Graphics.hpp>

#include "command.h"
#include "gameDrawable.h"

class Client{
public:
    Client();
    //void run();
private:
    //int id = {0};

    sf::RenderWindow window;
    sf::Event event;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;



    //std::function< void(Command) > verifyCommandCallback = std::bind( &GameDrawable::blah, game );
    CommandFunction verifyCommandCallback;
    //MenuDrawable menu;//TODO
    GameDrawable game;



    void eventLoop();
    void events();
    void update();
    void commandHandler(Command command);
    void render();

public:
    void commandSendTest();
    void commandSend(Command command);
    void commandRecv(Command command);
};
