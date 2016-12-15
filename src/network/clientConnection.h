#pragma once

#include <cstdlib>
#include <iostream>
#include <thread>
#include <functional>
#include <boost/asio.hpp>

#include "chatMessage.h"

typedef std::function<void(const std::string& msg)> ReadHandler;

class ClientConnection
{
public:
    ClientConnection(boost::asio::io_service& ioService,
        boost::asio::ip::tcp::resolver::iterator endpointIterator);
    ClientConnection(boost::asio::io_service& ioService,
        boost::asio::ip::tcp::resolver::iterator endpointIterator,
        ReadHandler rh);

    void write(const Message& msg);
    void write(const std::string& str);

    void close();

private:
    void doConnect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void doReadHeader();

    void doReadBody();

    void doWrite();



    boost::asio::io_service& ioService_;
    boost::asio::ip::tcp::socket socket_;
    Message readMessage_;
    MessageDeque writeMessages_;

    ReadHandler readHandler;
};
