#include "server_connection.h"


void Room::join(Participant_ptr participant)
{
    participants_.insert(participant);

    //map_[participant] = counter_;
    map_.insert({participant, counter_});
    ++counter_;

    game._join();
    /*for (auto msg: recent_msgs_)
        participant->deliver(msg);*/
}

void Room::leave(Participant_ptr participant)
{
    participants_.erase(participant);
}

void Room::deliver(const Message& msg)
{
    /*recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
        recent_msgs_.pop_front();*/

    for (auto participant: participants_)
        participant->deliver(msg);
}


void Room::readHandler(Participant_ptr p, const Message& msg)
{

    std::string msgString(msg.body(), msg.body_length());

    //std::cout << "readHandler start" << std::endl;
    /*int i(0);
    for (auto participant: participants_){
        if(p == participant){

            game._move(i, msgString);
        }
        ++i;
    }*/
    int j = map_.at(p);
    game._move(j, msgString);
    //std::cout << "readHandler stop" << std::endl;

    std::string stateString(game._state());
    Message stateMsg;
    stateMsg.body_length(std::strlen(stateString.c_str()));
    std::memcpy(stateMsg.body(), stateString.c_str(), stateMsg.body_length());
    stateMsg.encode_header();


    for (auto participant: participants_)
        participant->deliver(stateMsg);

    //deliver(response_msg_);// отправить всем
    //participant->deliver(response_msg_);// отправить конкретному игроку
}


//----------------------------------------------------------------------

ServerConnection::ServerConnection(boost::asio::ip::tcp::socket socket, Room& room) :
        socket_(std::move(socket)),
        room_(room)
{
}

void ServerConnection::start()
{
    room_.join(shared_from_this());
    do_read_header();
}

void ServerConnection::deliver(const Message& msg)
{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
        do_write();
    }
}

void ServerConnection::do_read_header()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), Message::header_length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec && read_msg_.decode_header())
            {
                do_read_body();
            }
            else
            {
                room_.leave(shared_from_this());
            }
        }
    );
}

void ServerConnection::do_read_body()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                //room_.deliver(read_msg_);
                room_.readHandler(shared_from_this(), read_msg_);
                do_read_header();


                //=========================== NEW BEGIN
                /*
                //game.handler(read_msg_)
                room_.gameHandler(shared_from_this(), read_msg_);{
                    response_msg_ = ...

                    room_.deliver(response_msg_);// отправить всем
                    deliver(response_msg_);// отправить конкретному игроку
                }
                do_read_header();
                */
                //=========================== NEW END
            }
            else
            {
                room_.leave(shared_from_this());
            }
        }
    );
}

void ServerConnection::do_write()
{
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                write_msgs_.pop_front();
                if (!write_msgs_.empty())
                {
                    do_write();
                }
            }
            else
            {
                room_.leave(shared_from_this());
            }
        }
    );
}
