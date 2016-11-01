#include <unistd.h>// close()
#include <memory>// std::shared_ptr

#include <iostream>// std::cerr

#include <string.h>
#include <netinet/in.h>// struct sockaddr_in
#include <netdb.h>// gethostbyname
#include <fcntl.h>// fcntl

class Socket{
public:
    Socket();
    Socket(int sd);
    ~Socket();

    void createServerSocket(uint32_t port, uint32_t queue_size)     throw (std::exception);
    void connect(const std::string &host, int port)                 throw (std::exception);
    void connect(const std::string &host, int port, int timeout)    throw (std::exception);
    std::shared_ptr<Socket> accept()                                throw (std::exception);
    void send(const std::string &s)                                 throw (std::exception);
    std::string my_recv()                                           throw (std::exception);
    std::string my_recv(size_t bytes)                               throw (std::exception);
    void close();

    bool hasData()                                                  throw (std::exception);
    void setRcvTimeout(int sec, int microsec)                       throw (std::exception);
    void setNonBlocked(bool opt)                                    throw (std::exception);
    void setReuseAddr(int sd)                                       throw (std::exception);


private:
    int m_Sd;
    
    std::string int2ipv4(uint32_t ip);
    struct sockaddr_in resolve(const char* host, int port);
    void set_non_blocked_impl(int sd, bool opt)                     throw (std::exception);
};
