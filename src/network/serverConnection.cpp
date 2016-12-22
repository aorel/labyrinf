#include "serverConnection.h"

void Room::join(ParticipantPtr participant){
    std::cout << "+connection: " << participant->getAddressString() << std::endl;
    participants_.insert(participant);

    map_.insert({participant, counter_});
    ++counter_;

    participant->deliver(game._info());
    map_[participant] = game._joinKey();
    participant->deliver(game._join());
    deliverExceptOne(participant, game._add());
}

void Room::leave(ParticipantPtr participant){
    std::cout << "-connection: " << participant->getAddressString() << std::endl;
    std::string msg = game._del(map_.at(participant));
    map_.erase(participant);
    participants_.erase(participant);
    deliver(msg);
}

void Room::deliver(const Message& msg){
    for(const auto& participant: participants_){
        participant->deliver(msg);
    }
}

void Room::deliverExceptOne(ParticipantPtr exceptParticipant, const Message& msg){
    for(const auto& participant: participants_){
        if(participant == exceptParticipant){
            continue;
        }
        participant->deliver(msg);
    }
}

void Room::readHandler(ParticipantPtr p, const Message& msg){

    std::string msgString(msg.body(), msg.getBodyLength());
    Message stateMsg(game._move(map_.at(p), msgString));

    for(const auto& participant: participants_){
        participant->deliver(stateMsg);
    }
}

//----------------------------------------------------------------------

ServerConnection::ServerConnection(boost::asio::ip::tcp::socket socket, Room& room) :
        socket_(std::move(socket)),
        room_(room){
}

void ServerConnection::start(){
    room_.join(shared_from_this());
    doReadHeader();
}

void ServerConnection::deliver(const Message& msg){
    bool write_in_progress = !writeMessages_.empty();
    writeMessages_.push_back(msg);
    if (!write_in_progress){
        doWrite();
    }
}

const std::string ServerConnection::getAddressString() const{
    return socket_.remote_endpoint().address().to_string();
}

void ServerConnection::doReadHeader(){
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(readMessage_.data(), Message::headerLength),
        [this, self](boost::system::error_code ec, std::size_t /*length*/){
            if (!ec && readMessage_.decodeHeader()){
                doReadBody();
            }
            else{
                room_.leave(shared_from_this());
            }
        }
    );
}

void ServerConnection::doReadBody(){
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(readMessage_.body(), readMessage_.getBodyLength()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/){
            if (!ec){
                //room_.deliver(readMessage_);
                room_.readHandler(shared_from_this(), readMessage_);
                doReadHeader();
            }
            else{
                room_.leave(shared_from_this());
            }
        }
    );
}

void ServerConnection::doWrite(){
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
        boost::asio::buffer(writeMessages_.front().data(),
          writeMessages_.front().length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/){
            if (!ec){
                writeMessages_.pop_front();
                if (!writeMessages_.empty()){
                    doWrite();
                }
            }
            else{
                room_.leave(shared_from_this());
            }
        }
    );
}
