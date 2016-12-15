#include "chatMessage.h"

Message::Message() :
        bodyLength_(0)
{
}

const char* Message::data() const
{
    return data_;
}

char* Message::data()
{
    return data_;
}

std::size_t Message::length() const
{
    return headerLength + bodyLength_;
}

const char* Message::body() const
{
    return data_ + headerLength;
}

char* Message::body()
{
    return data_ + headerLength;
}

std::size_t Message::bodyLength() const
{
    return bodyLength_;
}

void Message::bodyLength(std::size_t new_length)
{
    bodyLength_ = new_length;
    if (bodyLength_ > maxBodyLength)
        bodyLength_ = maxBodyLength;
}

bool Message::decodeHeader()
{
    char header[headerLength + 1] = "";
    std::strncat(header, data_, headerLength);
    bodyLength_ = std::atoi(header);
    if (bodyLength_ > maxBodyLength)
    {
        bodyLength_ = 0;
        return false;
    }
    return true;
}

void Message::encodeHeader()
{
    char header[headerLength + 1] = "";
    std::sprintf(header, "%4d", static_cast<int>(bodyLength_));
    std::memcpy(data_, header, headerLength);
}
