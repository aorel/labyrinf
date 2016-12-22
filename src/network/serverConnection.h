#pragma once

#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

#include "chatMessage.h"

#include "../game/game.h"

//----------------------------------------------------------------------

class Participant{
public:
    virtual ~Participant() {}
    virtual const std::string getAddressString() const = 0;
    virtual void deliver(const Message& msg) = 0;
};

typedef std::shared_ptr<Participant> ParticipantPtr;

//----------------------------------------------------------------------

class Room{
public:
    void join(ParticipantPtr participant);
    void leave(ParticipantPtr participant);

    void deliver(const Message& msg);
    void deliverExceptOne(ParticipantPtr exeptParticipant, const Message& msg);
    void readHandler(ParticipantPtr p, const Message& msg);

private:
    std::set<ParticipantPtr> participants_;

    Game game;
    int counter_{0};
    std::map<ParticipantPtr, int> map_;
};

//----------------------------------------------------------------------

class ServerConnection :
    public Participant,
    public std::enable_shared_from_this<ServerConnection>{
public:
    ServerConnection(boost::asio::ip::tcp::socket socket, Room& room);

    void start();

    void deliver(const Message& msg);

    const std::string getAddressString() const override;

private:
    void doReadHeader();

    void doReadBody();

    void doWrite();

    boost::asio::ip::tcp::socket socket_;
    Room& room_;
    Message readMessage_;
    MessageDeque writeMessages_;
};
