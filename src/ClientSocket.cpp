#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

#include "ClientSocket.h"
#include "ServerSocket.h"


ClientSocket::ClientSocket(){
    
    client_addr.sin_family = AF_INET;
    client_sockfd =  socket(this->client_addr.sin_family, SOCK_STREAM, 0);

    std::cout << "This is the ClientSocket constructor\n";
    
}

void ClientSocket::send_message_to_server(ServerSocket *server_socket, int client_sockfd, std::string message){
    send(client_sockfd, message.c_str(), message.length(), 0);
}

void ClientSocket::connect_to_server(ServerSocket *server_socket){

    

    if(connect(client_sockfd, (sockaddr*)&server_socket->get_server_addr(), sizeof(sockaddr_in)) < 0)
        std::cout << "Connection failed";

    std::string test_message = "Hello, test!";
    send_message_to_server(server_socket, client_sockfd, test_message);
    

}
