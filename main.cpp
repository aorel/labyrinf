#include <iostream>

#include <SFML/Graphics.hpp>

#include "labyrinf/game.h"
#include "labyrinf/client.h"
#include "labyrinf/server.h"

int main()
{
    /*if(arg == ...){
        Server server(ip, port, ...);
    }
    else{
        Client client();
    }*/

    Client client;
    client.run();

    //Game game;
    //game.run();

    return 0;
}
