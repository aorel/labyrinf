#include "chat_message.h"

Message::Message() :
        body_length_(0)
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
    return header_length + body_length_;
}

const char* Message::body() const
{
    return data_ + header_length;
}

char* Message::body()
{
    return data_ + header_length;
}

std::size_t Message::body_length() const
{
    return body_length_;
}

void Message::body_length(std::size_t new_length)
{
    body_length_ = new_length;
    if (body_length_ > max_body_length)
        body_length_ = max_body_length;
}

bool Message::decode_header()
{
    char header[header_length + 1] = "";
    std::strncat(header, data_, header_length);
    body_length_ = std::atoi(header);
    if (body_length_ > max_body_length)
    {
        body_length_ = 0;
        return false;
    }
    return true;
}

void Message::encode_header()
{
    char header[header_length + 1] = "";
    std::sprintf(header, "%4d", static_cast<int>(body_length_));
    std::memcpy(data_, header, header_length);
}