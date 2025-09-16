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

void ClientSocket::send_message_to_server(int client_sockfd, std::string message){
    int bytes_sent = send(client_sockfd, message.c_str(), message.length(), 0);

    if(bytes_sent < 0)
        std::cout << "Send failed\n";
    else
        std::cout << "Bytes sent succesfully\n";

}

void ClientSocket::connect_to_server(ServerSocket *server_socket){

    

    if(connect(client_sockfd, (sockaddr*)&server_socket->get_server_addr(), sizeof(sockaddr_in)) < 0)
        std::cout << "Connection failed";

    std::string test_message = "Hello, test!";
    send_message_to_server(client_sockfd, test_message);
    

}

int ClientSocket::get_client_socket(){
     return this->client_sockfd;
}