#include "socket.h"

struct sockaddr_in resolve(const char* host, int port)
{
    struct hostent* hp = gethostbyname(host);
    if (NULL == hp)
        throw std::runtime_error("resolve error: " + std::string(strerror(errno)));

    char** pAddr = hp->h_addr_list;
    while(*pAddr)
    {
        unsigned char *ipf = reinterpret_cast<unsigned char*>(*pAddr);
        uint32_t cur_interface_ip = 0;
        uint8_t *rimap_local_ip_ptr = reinterpret_cast<uint8_t*>(&cur_interface_ip);
        rimap_local_ip_ptr[0] = ipf[0];
        rimap_local_ip_ptr[1] = ipf[1];
        rimap_local_ip_ptr[2] = ipf[2];
        rimap_local_ip_ptr[3] = ipf[3];
        std::cerr << "resolved: " << int2ipv4(cur_interface_ip) << std::endl;
        ++pAddr;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = /*Address Family*/AF_INET;        // only AF_INET !
    addr.sin_port = htons(port);
    memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);

    return addr;
}

void set_non_blocked_impl(int sd, bool opt) throw (std::exception)
{
    int flags = fcntl(sd, F_GETFL, 0);
    int new_flags = (opt)? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    if (fcntl(sd, F_SETFL, new_flags) == -1)
        throw std::runtime_error("make nonblocked: " + std::string(strerror(errno)));
}

std::string int2ipv4(uint32_t ip)
{
    char buf[128];
    snprintf(buf, sizeof(buf), "%u.%u.%u.%u", ip&0xFF, (ip&0xFF00) >> 8, (ip&0xFF0000) >> 16, (ip&0xFF000000) >> 24);
    return buf;
}









std::string Socket::my_recv() throw (std::exception)
{
    char buf[256];
#ifdef __APPLE__
    // mac os x don't defines MSG_NOSIGNAL
    int n = ::recv(m_Sd, buf, sizeof(buf), 0);
#else
    int n = ::recv(m_Sd, buf, sizeof(buf), MSG_NOSIGNAL);
#endif

    if (-1 == n && errno != EAGAIN)
        throw std::runtime_error("read failed: " + std::string(strerror(errno)));
    if (0 == n)
        throw std::runtime_error("client: " + std::to_string(m_Sd) + " disconnected");
    if (-1 == n)
        throw std::runtime_error("client: " + std::to_string(m_Sd) + " timeouted");

    std::string ret(buf, buf + n);
    while (ret.back() == '\r' || ret.back() == '\n')
        ret.pop_back();
    std::cerr << "client: " << m_Sd << ", recv: " << ret << " [" << n << " bytes]" << std::endl;
    return ret;
}

std::string Socket::my_recv(size_t bytes) throw (std::exception)
{
    char *buf = new char[bytes];
    size_t r = 0; 
    while (r != bytes)
    {    
        ssize_t rc = ::recv(m_Sd, buf + r, bytes - r, 0);
        std::cerr << "recv_ex: " << rc << " bytes\n";

        if (rc == -1 || rc == 0)
        {
            delete [] buf;
            throw std::runtime_error("read failed: " + std::string(strerror(errno)));
        }
        r += rc;
    }
    std::string ret(buf, buf + bytes);
    delete [] buf;
    return ret;
}

void Socket::setRcvTimeout(int sec, int microsec) throw (std::exception)
{
    struct timeval tv;
    tv.tv_sec = sec;
    tv.tv_usec = microsec;

    if (setsockopt(m_Sd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) != 0)
        throw std::runtime_error("set rcvtimeout: " + std::string(strerror(errno)));
}

void Socket::send(const std::string &str) throw (std::exception)
{
    size_t left = str.size();
    ssize_t sent = 0;
    //int flags = MSG_DONTWAIT | MSG_NOSIGNAL;
    int flags = 0;

    while (left > 0)
    {
        sent = ::send(m_Sd, str.data() + sent, str.size() - sent, flags);
        if (-1 == sent)
            throw std::runtime_error("write failed: " + std::string(strerror(errno)));

        left -= sent;
    }
}

void Socket::setReuseAddr(int sd) throw (std::exception)
{
    int yes = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        ::close(sd);
        throw std::runtime_error("setopt: " + std::string(strerror(errno)));
    }
}


void Socket::connect(const std::string &host, int port) throw (std::exception)
{
    struct sockaddr_in addr = resolve(host.data(), port);

    int sd = socket(/*Protocol Family*/PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd <= 0)
        throw std::runtime_error("error to create socket: " + std::string(strerror(errno)));

    int connected = ::connect(sd, (struct sockaddr*)&addr, sizeof(addr));
    if (connected == -1)
    {
        ::close(sd);
        throw std::runtime_error("connect error: " + std::string(strerror(errno)));
    }

    m_Sd = sd;
}

void Socket::connect(const std::string &host, int port, int timeout) throw (std::exception)
{
    struct sockaddr_in addr = resolve(host.data(), port);

    int sd = socket(/*Protocol Family*/PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd <= 0)
        throw std::runtime_error("error to create socket: " + std::string(strerror(errno)));

    set_non_blocked_impl(sd, true);

    int connected = ::connect(sd, (struct sockaddr*)&addr, sizeof(addr));
    if (connected == -1 && errno != EINPROGRESS)
    {
        ::close(sd);
        throw std::runtime_error("connect error: " + std::string(strerror(errno)));
    }

    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_SET(sd, &write_fds);
    struct timeval tm;
    tm.tv_sec = timeout;
    tm.tv_usec = 0;
    int sel = select(sd + 1, /*read*/NULL, /*write*/&write_fds, /*exceptions*/NULL, &tm);

    if (sel != 1)
    {
        ::close(sd);
        throw std::runtime_error("connect timeout");
    }

    m_Sd = sd;
}

std::shared_ptr<Socket> Socket::accept() throw (std::exception)
{
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    socklen_t cli_len = sizeof(client);

    int cli_sd = ::accept(m_Sd, (struct sockaddr*)&client, &cli_len);
    if (-1 == cli_sd)
        return std::shared_ptr<Socket>();
    std::cerr << "new client: " << cli_sd << ", from: " << int2ipv4(client.sin_addr.s_addr) << std::endl;
    
    return std::make_shared<Socket>(cli_sd);
}

void Socket::createServerSocket(uint32_t port, uint32_t listen_queue_size) throw (std::exception)
{
    int sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd <= 0)
        throw std::runtime_error("socket: " + std::string(strerror(errno)));

    setReuseAddr(sd);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (::bind(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        ::close(sd);
        throw std::runtime_error("bind: " + std::string(strerror(errno)));
    }

    ::listen(sd, listen_queue_size);
    m_Sd = sd;
}