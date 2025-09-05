#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <netinet/in.h>  // sockaddr_in
#include <string>

// #include "ClientSocket.h"

class ClientSocket;

class ServerSocket {
private:
    sockaddr_in server_addr; //sockaddr_in specifically for ipv4

public:
    ServerSocket();
    void create_tcp_server(ClientSocket *client_socket);

    const sockaddr_in& get_server_addr();
};

#endif
