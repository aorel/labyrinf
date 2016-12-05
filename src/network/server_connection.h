#pragma once

#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

#include "chat_message.h"

//----------------------------------------------------------------------

class Participant
{
public:
    virtual ~Participant() {}
    virtual const std::string get_address_string() const = 0;
    virtual void deliver(const Message& msg) = 0;
};

typedef std::shared_ptr<Participant> Participant_ptr;

//----------------------------------------------------------------------

#include "../game/game.h"

class Room
{
public:
    void join(Participant_ptr participant);
    void leave(Participant_ptr participant);

    void deliver(const Message& msg);
    void readHandler(Participant_ptr p, const Message& msg);

private:
    std::set<Participant_ptr> participants_;

    Game game;
    int counter_{0};
    std::map<Participant_ptr, int> map_;

    /*enum { max_recent_msgs = 100 };
    Message_deque recent_msgs_;*/
};

//----------------------------------------------------------------------
class Room;
class ServerConnection :
    public Participant,
    public std::enable_shared_from_this<ServerConnection>
{
public:
    ServerConnection(boost::asio::ip::tcp::socket socket, Room& room);

    void start();

    void deliver(const Message& msg);

    const std::string get_address_string() const override;

private:
    void do_read_header();

    void do_read_body();

    void do_write();

    boost::asio::ip::tcp::socket socket_;
    Room& room_;
    Message read_msg_;
    Message_deque write_msgs_;
};
