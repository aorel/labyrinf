#include "client_connection.h"

ClientConnection::ClientConnection(boost::asio::io_service& io_service,
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator) :
        io_service_(io_service),
        socket_(io_service),
        readHandler([](const std::string msg){})
{
    do_connect(endpoint_iterator);
}

ClientConnection::ClientConnection(boost::asio::io_service& io_service,
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator,
    ReadHandler rh) :
        ClientConnection(io_service, endpoint_iterator)
        //io_service_(io_service),
        //socket_(io_service),
        //readHandler(rh)

{
    //do_connect(endpoint_iterator);
    readHandler = rh;
}

void ClientConnection::write(const Message& msg)
{
    io_service_.post(
        [this, msg]()
        {
            bool write_in_progress = !write_msgs_.empty();
            write_msgs_.push_back(msg);
            if (!write_in_progress)
            {
                do_write();
            }
        }
    );
}

void ClientConnection::write(const std::string& str){
    Message msg;
    msg.body_length(std::strlen(str.c_str()));
    std::memcpy(msg.body(), str.c_str(), msg.body_length());
    msg.encode_header();
    write(msg);
}

void ClientConnection::close()
{
    io_service_.post([this]() { socket_.close(); });
}

void ClientConnection::do_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
    boost::asio::async_connect(socket_, endpoint_iterator,
        [this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator)
        {
            if (!ec)
            {
                do_read_header();
            }
        }
    );
}

void ClientConnection::do_read_header()
{
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), Message::header_length),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec && read_msg_.decode_header())
            {
                do_read_body();
            }
            else
            {
                socket_.close();
            }
        }
    );
}

void ClientConnection::do_read_body()
{
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            std::cout.write(read_msg_.body(), read_msg_.body_length());
            std::cout << "\n";

            std::string str(read_msg_.body(), read_msg_.body_length());
            readHandler(str);


            do_read_header();
          }
          else
          {
            socket_.close();
          }
        }
    );
}

void ClientConnection::do_write()
{
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(),
        write_msgs_.front().length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
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
                socket_.close();
            }
        }
    );
}
