#include "server.h"

Server::Server(boost::asio::io_service& io_service,
    const boost::asio::ip::tcp::endpoint& endpoint) :
        acceptor_(io_service, endpoint),
        socket_(io_service){
    doAccept();
}

void Server::doAccept(){
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
            if (!ec){
                std::make_shared<ServerConnection>(std::move(socket_), room_)->start();
            }

            doAccept();
        }
    );
}
