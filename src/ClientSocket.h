#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

// #include "ServerSocket.h"

class ServerSocket;

class ClientSocket{

    private:
         sockaddr_in client_addr;
         int client_sockfd;
        //  ServerSocket *server_socket;

    public:
        ClientSocket();

        void connect_to_server(ServerSocket *server_socket);

        void send_message_to_server(int client_sockfd, std::string message);

        int get_client_socket();

        sockaddr_in& get_client_addr();

        void trying_ports(ServerSocket *server_socket);
    
};


#endif