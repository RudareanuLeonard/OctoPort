// #include <sys/socket.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class ServerSocket{
    private:
        sockaddr_in serverAddr; // sockaddr_in is a struct that is used when working with ipv4 specifically
        // sockaddr serverSocket; //sockaddr is a struct that is used when working with both ipv4 and ipv6
    public:
        ServerSocket(){
            // serverSocket.
            // serverSocket.sa_family = AF_INET; //IPV4 SOCKET

            serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
            serverAddr.sin_port = 8080;
            
            this->serverAddr = serverAddr;
        }

        void create_tcp_server(){

            //create the socket file descriptor; is int because fd is a number in the kernel table
            int sockfd = socket(AF_INET, SOCK_STREAM, 0); //ipv4, tcp

            bind(sockfd, (sockaddr*)&this->serverAddr.sin_addr.s_addr, sizeof(this->serverAddr.sin_addr.s_addr)); //giving socket file descriptor a local address

            std::cout << "Let's start listening on server:";

            while(true)
                listen(sockfd, 10);

        }



};