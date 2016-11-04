#include <iostream>

#include <SFML/Graphics.hpp>

#include "src/client.h"
#include "src/server.h"

/*

1. Сделать рисователь игры (дружественный к классу Game???), удалить все все классы "*Drawable.*"
2. Позиция перескакивает 0
3. Как понять, что клиент отвалился?
4. Неблокрующий сокет для сервера под Linux, для клиента под Windows придется писать другую реализацию сокета
5. Добавить сецификатор const где необходимо

*/


int main(int argc, char *argv[]){
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
            Server server(port);
        }
        else if(argc == 3){
            std::string host(argv[1]);
            int port = std::stoi(argv[2]);
            std::cout << "client trying to connect " << host << ":" << port << "..." << std::endl;
            Client client;
        }
        else{
            std::cout << "[error] wrong arguments" << std::endl;
        }
    }
    else{
        std::cout << "client starting on localhost..." << std::endl;
        Client client;
    }

    return 0;
}
