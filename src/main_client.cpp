#include <iostream>
#include "ClientSocket.h"
#include "ServerSocket.h"

int main(){
    ClientSocket client_socket;
    ServerSocket server_socket;


    client_socket.connect_to_server(&server_socket);
}