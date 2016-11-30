#pragma once

#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

#include "network/chat_message.h"

//----------------------------------------------------------------------

class Participant
{
public:
    virtual ~Participant() {}
    virtual void deliver(const Message& msg) = 0;
};

typedef std::shared_ptr<Participant> Participant_ptr;

//----------------------------------------------------------------------

class Room
{
public:
    void join(Participant_ptr participant);

    void leave(Participant_ptr participant);

    void deliver(const Message& msg);

private:
    std::set<Participant_ptr> participants_;
    /*enum { max_recent_msgs = 100 };
    Message_deque recent_msgs_;*/
};

//----------------------------------------------------------------------

class Session :
    public Participant,
    public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket socket, Room& room);

    void start();

    void deliver(const Message& msg);

private:
    void do_read_header();

    void do_read_body();

    void do_write();

    boost::asio::ip::tcp::socket socket_;
    Room& room_;
    Message read_msg_;
    Message_deque write_msgs_;
};

//----------------------------------------------------------------------

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
