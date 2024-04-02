#ifndef UDP_LIB_HPP
#define UDP_LIB_HPP

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

const int DEF_BUFFER_SIZE = 1024;

namespace udp_client_server
{

class udp_srv{
    public:
    udp_srv() = default;
    udp_srv(int port, char* addr)
        :port{port},
        addr{addr}
    {};
    udp_srv(int port)
        :port{port}
    {};

    int                 port;
    char*               addr;
    struct sockaddr_in  Addr_s;
    socklen_t addrLen;
};

class udp_client{
    public:
    udp_client() = default;
    udp_client(int port, char* addr)
        :port{port},
        addr{addr}
    {};
    int                 port;
    char*               addr;
    struct sockaddr_in  Addr_s;
    socklen_t addrLen;
};


class udp_cs
{
public:
    udp_cs(int port);
    udp_cs(const std::string& addr, int port);
    ~udp_cs();

    udp_srv server;
    udp_srv client;

    std::string         get_server_addr();
    int                 get_server_port();
    std::string         get_client_addr();
    int                 get_client_port();

    int                 send(const char *msg);
    int                 send(const char *msg, const char *addr);
    int                 send(const char *msg, const char *addr, int port);
    void                get(char* buf);

private:

    int sockfd;

};

} // namespace udp_client_server

#endif