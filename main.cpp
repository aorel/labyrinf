#include <iostream>

#include <SFML/Graphics.hpp>

#include "labyrinf/game.h"
#include "labyrinf/client.h"
#include "labyrinf/server.h"

/*

1. Сделать рисователь игры (дружественный к классу Game???), удалить все все классы "*Drawable.*"
2.
3.
4.
5.

*/


int main(int argc, char *argv[])
{
    std::cout << "arguments:";
    for(int i(1); i<argc; ++i){
        std::cout << ' ' << argv[i];
    }
    std::cout << std::endl;
    std::cout << std::endl;

    if(argc > 1){
        if(argc == 2){
            int port = std::stoi(std::string(argv[1]));
            std::cout << "server starting on port " << port << "..." << std::endl;
            //port = 0;
            Server server(port);
        }
        else if(argc == 3){
            std::string host(argv[1]);
            int port = std::stoi(argv[2]);
            std::cout << "client trying to connect " << host << ":" << port << "..." << std::endl;
            Client client;
            //client.run();
        }
        else{
            std::cout << "[error] wrong arguments" << std::endl;
        }
    }
    else{
        std::cout << "client starting on localhost..." << std::endl;
        Client client;
        //client.run();
    }

    return 0;
}
