#include <iostream>
#include "ClientSocket.h"
#include "ServerSocket.h"

int main(){
    ClientSocket client_socket;
    ServerSocket server_socket;

    server_socket.create_tcp_server(&client_socket);
}