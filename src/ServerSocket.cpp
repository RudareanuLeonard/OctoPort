#include "ServerSocket.h"
#include "ClientSocket.h"

#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> // for close()




ServerSocket::ServerSocket() {
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);  // Use htons for correct byte order
}

void ServerSocket::create_tcp_server(ClientSocket *client_socket) {
    int sockfd = socket(this->server_addr.sin_family, SOCK_STREAM, 0); // file descriptor; is int because is a number in the kernel table
    if (sockfd < 0) {
        std::cout << "Error creating socket\n";
        return;
    }

    // bind socket
    if (bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cout << "Error binding socket\n";
        close(sockfd);
        return;
    }

    std::cout << "Server started at " << inet_ntoa(server_addr.sin_addr) << ":" << ntohs(server_addr.sin_port) << "\n";

    // listen for connections
    if (listen(sockfd, 10) < 0) {
        std::cout<< "Error listening\n";
        close(sockfd);
        return;
    }

    std::cout << "Listening for connections...\n";

    socklen_t client_len = sizeof(client_socket->get_client_addr());
    sockaddr_in &addr = client_socket->get_client_addr();

    int accept_conn_socket = accept(sockfd, (sockaddr*)&addr, &client_len);

    if(accept_conn_socket < 0)
        std::cout << "Error in accepting connections...\n";


    char buffer[1024] = {0};
    int bytes_message_received = recv(accept_conn_socket, buffer, sizeof(buffer), 0);

    if(bytes_message_received > 0)
        std::cout << "Message received: " << buffer << "\n";
    else
        std::cout << "Message not received\n";


    // keeping the server alive
    while (true) {
    }

    close(sockfd);
}

const sockaddr_in& ServerSocket::get_server_addr(){
    return this->server_addr;
}

    
