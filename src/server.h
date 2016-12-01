#pragma once

#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

#include "network/server_connection.h"

class Server
{
public:
    Server(boost::asio::io_service& io_service,
        const boost::asio::ip::tcp::endpoint& endpoint);

private:
    void do_accept();

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    Room room_;
};
