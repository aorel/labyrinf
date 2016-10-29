#include <iostream>

#include <SFML/Graphics.hpp>

#include "labyrinf/game.h"
#include "labyrinf/client.h"
#include "labyrinf/server.h"

int main(int argc, char *argv[])
{
    if(argc > 1){
        std::cout << "arguments:" << std::endl;
        for(int i(1); i<argc; ++i){
            std::cout << argv[i] << '\n';
        }

        if(argc == 2){
            
            int port = std::stoi(std::string(argv[1]));
            std::cout << "server starting on port " << port << "..." << std::endl;
            //port = 0;
            Server server(port);
        }
        else{
            std::cout << "wrong arguments" << std::endl;
        }
    }
    else{
        printf("client: ...");
        Client client;
        client.run();
    }

    //Client client;
    //client.run();



    //Game game;
    //game.run();

    return 0;
}
