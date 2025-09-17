#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>

#include "ClientSocket.h"
#include "ServerSocket.h"


ClientSocket::ClientSocket(){
    
    client_addr.sin_family = AF_INET;
    client_sockfd =  socket(this->client_addr.sin_family, SOCK_STREAM, 0);

    std::cout << "This is the ClientSocket constructor\n";
    
}


sockaddr_in& ClientSocket::get_client_addr(){
    return this->client_addr;
}


void ClientSocket::trying_ports(ServerSocket *server_socket){
    int start_port = 8070;
    int end_port = 8090;
    int timeout = 200; //milliseconds

    std::cout << "I am going to scan localhost ports: " << start_port << " - " << end_port;

    sockaddr_in client_addr = this->get_client_addr();

    for(int p = start_port; p <= end_port; p ++){
        std::cout << "Current port is " << p << "\n";
        int temp_socket = socket(client_addr.sin_family, SOCK_STREAM, 0); // a new socket for each port

        int flag = fcntl(temp_socket, F_GETFD); // get value of flag of the current file descriptor

        if(flag < 0){
            std::cout << "Error on flag!\n";
            flag = 0; //we set it to 0 because on the next line we will set the flag and we want to avoid setting it to -1 (which is error)
        }
        fcntl(temp_socket, F_SETFL, flag | O_NONBLOCK); // O_NONBLOCK is to avoid waiting until socket fails (because most functions blocks)


        sockaddr_in server_addr = server_socket->get_server_addr();
        int res = connect(temp_socket, (sockaddr*)&server_addr, sizeof(server_addr));

        if (res == 0) {
            std::cout << "Port " << p << " is OPEN\n";
            close(temp_socket);
            continue;
        }

        timeval time_val;
        time_val.tv_sec = timeout / 1000;
        time_val.tv_usec = (timeout % 1000) * 1000;

        //select syscall is allowing u monitor multimple file descriptors
        //select is going to tell you when there is something to read on any fds
        fd_set setting_fds;
        FD_ZERO(&setting_fds); // initialize the set for select
        FD_SET(temp_socket, &setting_fds);// add s to the set

        int sel = select(temp_socket + 1, nullptr, &setting_fds, nullptr, &time_val); 
        if (sel > 0 && FD_ISSET(temp_socket, &setting_fds)){
            int so_error = 0;
            socklen_t len = sizeof(so_error);
            getsockopt(temp_socket, SOL_SOCKET, SO_ERROR, &so_error, &len);
            
            if (so_error == 0) {
                std::cout << "Port " << p << " is OPEN\n";
            }
    }
    close(temp_socket);
}

std::cout << "Scan finished\n";
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

