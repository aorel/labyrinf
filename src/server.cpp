#include "server.h"

Server::Server(int p) :
        port(p){
    //socket_my(port, 1){
    
    
    
    //test_simple_server_();
    test_multiplexing_server_();
}





void Server::test_simple_server_(){
    try{
        Socket s;
        s.createServerSocket(port, 1);

        while(true){
            std::shared_ptr<Socket> client = s.accept();
            test_client_work_(client);
        }
    }
    catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}

void Server::test_multiplexing_server_(){
    try{
        Socket s;
        s.createServerSocket(port, 1);
        s.setNonBlocked(true);

        while(true){
            usleep(100);
            while (auto client = s.accept()){
                client->setNonBlocked(true);
                multiplexing_clients.push_back(client);
            }

            for(const auto& s : multiplexing_clients){
                if(s->hasData()){
                    std::string line = s->my_recv();
                    s->send("echo: " + line + "\n");
                }
            }
        }
    }
    catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}

void Server::test_client_work_(std::shared_ptr<Socket> client){
    client->setRcvTimeout(/*sec*/30, /*microsec*/0);
    while (true) try{
        std::string line = client->my_recv();
        client->send("echo: " + line + "\n");
    }
    catch(const std::exception &e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return;
    }
}
