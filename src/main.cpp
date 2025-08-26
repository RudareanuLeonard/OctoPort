#include <iostream>
#include <sys/socket.h>

#include "ServerSocket.cpp"

int main(){
    // std::cout << "test";

    ServerSocket server_socket = ServerSocket();

    

    while(true)
        server_socket.create_tcp_server();
}






