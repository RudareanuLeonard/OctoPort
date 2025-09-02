#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ClientSocket.h"
#include "ServerSocket.h"


ClientSocket::ClientSocket(){
    
    client_addr.sin_family = AF_INET;

    std::cout << "This is the ClientSocket constructor\n";
    
}

void ClientSocket::connect_to_server(ServerSocket *server_socket){

    int client_sockfd =  socket(inet_addr("127.0.0.1"), SOCK_STREAM, 0);

    if(connect(client_sockfd, (sockaddr*)&server_socket->get_server_addr(), 100) < 0)
        std::cout << "Connection failed";

}