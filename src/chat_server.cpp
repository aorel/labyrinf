#include "chat_server.h"

void Room::join(Participant_ptr participant)
{
    participants_.insert(participant);
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

//----------------------------------------------------------------------

Session::Session(boost::asio::ip::tcp::socket socket, Room& room) :
        socket_(std::move(socket)),
        room_(room)
{
}

void Session::start()
{
    room_.join(shared_from_this());
    do_read_header();
}

void Session::deliver(const Message& msg)
{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
        do_write();
    }
}

void Session::do_read_header()
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

void Session::do_read_body()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                room_.deliver(read_msg_);
                do_read_header();
            }
            else
            {
                room_.leave(shared_from_this());
            }
        }
    );
}

void Session::do_write()
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

//----------------------------------------------------------------------

Server::Server(boost::asio::io_service& io_service,
    const boost::asio::ip::tcp::endpoint& endpoint) :
        acceptor_(io_service, endpoint),
        socket_(io_service)
{
    do_accept();
}

void Server::do_accept()
{
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket_), room_)->start();
            }

            do_accept();
        }
    );
}
