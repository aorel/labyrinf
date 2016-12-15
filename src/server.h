#pragma once

#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

#include "network/serverConnection.h"

class Server
{
public:
    Server(boost::asio::io_service& ioService,
        const boost::asio::ip::tcp::endpoint& endpoint);

private:
    void doAccept();

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    Room room_;
};
