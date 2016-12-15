#include "clientConnection.h"

ClientConnection::ClientConnection(boost::asio::io_service& ioService,
    boost::asio::ip::tcp::resolver::iterator endpointIterator) :
        ioService_(ioService),
        socket_(ioService),
        readHandler([](const std::string msg){})
{
    doConnect(endpointIterator);
}

ClientConnection::ClientConnection(boost::asio::io_service& ioService,
    boost::asio::ip::tcp::resolver::iterator endpointIterator,
    ReadHandler rh) :
        ClientConnection(ioService, endpointIterator)
        //ioService_(io_service),
        //socket_(io_service),
        //readHandler(rh)

{
    //do_connect(endpointIterator);
    readHandler = rh;
}

void ClientConnection::write(const Message& msg)
{
    ioService_.post(
        [this, msg]()
        {
            bool writeInProgress = !writeMessages_.empty();
            writeMessages_.push_back(msg);
            if (!writeInProgress)
            {
                doWrite();
            }
        }
    );
}

void ClientConnection::write(const std::string& str){
    Message msg;
    msg.bodyLength(std::strlen(str.c_str()));
    std::memcpy(msg.body(), str.c_str(), msg.bodyLength());
    msg.encodeHeader();
    write(msg);
}

void ClientConnection::close()
{
    ioService_.post([this]() { socket_.close(); });
}

void ClientConnection::doConnect(boost::asio::ip::tcp::resolver::iterator endpointIterator)
{
    boost::asio::async_connect(socket_, endpointIterator,
        [this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator)
        {
            if (!ec)
            {
                doReadHeader();
            }
        }
    );
}

void ClientConnection::doReadHeader()
{
    boost::asio::async_read(socket_,
        boost::asio::buffer(readMessage_.data(), Message::headerLength),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec && readMessage_.decodeHeader())
            {
                doReadBody();
            }
            else
            {
                socket_.close();
            }
        }
    );
}

void ClientConnection::doReadBody()
{
    boost::asio::async_read(socket_,
        boost::asio::buffer(readMessage_.body(), readMessage_.bodyLength()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            std::cout.write(readMessage_.body(), readMessage_.bodyLength());
            std::cout << "\n";

            std::string str(readMessage_.body(), readMessage_.bodyLength());
            readHandler(str);


            doReadHeader();
          }
          else
          {
            socket_.close();
          }
        }
    );
}

void ClientConnection::doWrite()
{
    boost::asio::async_write(socket_,
        boost::asio::buffer(writeMessages_.front().data(),
        writeMessages_.front().length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                writeMessages_.pop_front();
                if (!writeMessages_.empty())
                {
                    doWrite();
                }
            }
            else
            {
                socket_.close();
            }
        }
    );
}
