#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <netinet/in.h>  // sockaddr_in
#include <string>

class ServerSocket {
private:
    sockaddr_in server_addr; //sockaddr_in specifically for ipv4

public:
    ServerSocket();
    void create_tcp_server();

    const sockaddr_in get_server_addr();
};

#endif
