#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>

class Message
{
public:
    enum { headerLength = 4 };
    enum { maxBodyLength = 512 };

    Message();

    const char* data() const;

    char* data();

    std::size_t length() const;

    const char* body() const;

    char* body();

    std::size_t bodyLength() const;

    void bodyLength(std::size_t newLength);

    bool decodeHeader();

    void encodeHeader();

private:
    char data_[headerLength + maxBodyLength];
    std::size_t bodyLength_;
};

typedef std::deque<Message> MessageDeque;
