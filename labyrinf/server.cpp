#include "server.h"

Server::Server(int p) :
        port(p){
        //socket_my(port, 1){
    try
    {
        //Socket s;
        my_socket.createServerSocket(port, 10);

        while(true)
        {
            std::shared_ptr<Socket> client = my_socket.accept();
            client_work(client);
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    
    
    
    
    
    
    /*
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0){
        //on_error("Could not create socket\n");
        printf("Could not create socket\n");
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt_val = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

    err = bind(server_fd, (struct sockaddr *) &server, sizeof(server));
    if (err < 0){
        //on_error("Could not bind socket\n");
        printf("Could not bind socket\n");
    }

    err = listen(server_fd, 128);
    if (err < 0){
        //on_error("Could not listen on socket\n");
        printf("Could not listen on socket\n");
    }

    printf("Server is listening on %d\n", port);

    while (1) {
        socklen_t client_len = sizeof(client);
        client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);

        if (client_fd < 0){
            //on_error("Could not establish new connection\n");
            printf("Could not establish new connection\n");
        }

        while (1) {
            int read = recv(client_fd, buffer, settings::server_buffer_size, 0);

            if (!read) break; // done reading
            if (read < 0){
                //on_error("Client read failed\n");
                printf("Client read failed\n");
            }

            err = send(client_fd, buffer, read, 0);
            if (err < 0){
                //on_error("Client write failed\n");
                printf("Client write failed\n");
            }
        }
    }
    */
}

void Server::client_work(std::shared_ptr<Socket> client)
{
    client->setRcvTimeout(/*sec*/30, /*microsec*/0);
    while (true) try
    {
        std::string line = client->my_recv();
        client->send("echo: " + line + "\n");
    }
    catch(const std::exception &e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return;
    }
}
