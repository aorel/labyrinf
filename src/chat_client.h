#pragma once

#include <cstdlib>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

#include "network/chat_message.h"

class Client
{
public:
    Client(boost::asio::io_service& io_service,
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void write(const Message& msg);

    void close();

private:
    void do_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void do_read_header();

    void do_read_body();

    void do_write();

private:
    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::socket socket_;
    Message read_msg_;
    Message_deque write_msgs_;
};
