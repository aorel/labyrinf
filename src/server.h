#pragma once

#include "game/game.h"
#include "network/socket.h"

class Server{
public:
    Server(int port);

private:

    int port = settings::server_defualt_port;
    Socket my_socket;
    
    std::vector<std::shared_ptr<Socket>> multiplexing_clients;
    std::vector<std::pair<std::shared_ptr<Socket>, std::shared_ptr<Game>>> clients;

    Game game;



    void test_simple_server_();
    void test_multiplexing_server_();
    void test_client_work_(std::shared_ptr<Socket> client);
};
