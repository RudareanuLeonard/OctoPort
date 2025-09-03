#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ServerSocket.h"

class ClientSocket{

    private:
         sockaddr_in client_addr;
        //  ServerSocket *server_socket;

    public:
        ClientSocket();

        void connect_to_server(ServerSocket *server_socket);
    
};


#endif