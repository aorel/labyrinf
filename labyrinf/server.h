#pragma once

#include "game.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "socket.h"

class Server{
public:
    Server(int port);

private:

    int port = settings::server_defualt_port;
    Socket my_socket;

    //int buffer_size = settings::buffer_size;
    char buffer[settings::server_buffer_size];
    int server_fd = 0;
    int client_fd, err;
    struct sockaddr_in server, client;


    Game game;
};
