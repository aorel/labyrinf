#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "command.h"
#include "game/gameDrawable.h"

struct CurrentPlay
{
    int index;
    bool isLife;
    CurrentPlay(int _index = 0, bool _isLife = 1) : index(_index), isLife(_isLife) {}
};

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


    typedef enum ClientState{
        MEMU,
        GAME,
    } ClientState;
    
    ClientState state = GAME;

    //MenuDrawable menu;//TODO
    GameDrawable game;
    
    //std::function< void(Command) > verifyCommandCallback = std::bind( &GameDrawable::blah, game );
    //CommandFunction verifyCommandCallback;
    std::function< void(Command command) > commandHandler;
    
    std::vector<CurrentPlay> arrayPlayers;

    void eventLoop();
    void events();
    void update();
    void menuCommandHandler(Command command);
    void playerActionHandler(Command command);
    void render();

public:
    void commandSendTest();
    void commandSend(Command command);
    void commandRecv(Command command);
};


