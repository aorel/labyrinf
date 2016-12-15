#pragma once

#include <cstdlib>
#include <iostream>
#include <thread>
#include <functional>
#include <boost/asio.hpp>

#include "chat_message.h"

typedef std::function<void(const std::string& msg)> ReadHandler;

class ClientConnection
{
public:
    ClientConnection(boost::asio::io_service& io_service,
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    ClientConnection(boost::asio::io_service& io_service,
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator,
        ReadHandler rh);

    void write(const Message& msg);
    void write(const std::string& str);

    void close();

private:
    void do_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void do_read_header();

    void do_read_body();

    void do_write();



    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::socket socket_;
    Message read_msg_;
    Message_deque write_msgs_;

    ReadHandler readHandler;
};
