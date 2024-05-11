#include <stdio.h>
#include <winsock.h>
#define MAXCLIENT 5
#define BUFFER_SIZE 1024

int main(){
    // Initialize Winsock
    WSADATA wsadata;
    WSAStartup(0x101, &wsadata);

    /*
        Server Information 
            IP: 127.0.0.1
            PORT: 1234
    */
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(1234);

    // Create a socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);

    connect(server_socket, (LPSOCKADDR)&server, sizeof(server));
    printf("Connected to server\n");
    u_short mode = 1;
    ioctlsocket(server_socket, FIONBIO, &mode);
    while (TRUE){
        char buffer[BUFFER_SIZE];
        int n =recv(server_socket, buffer, BUFFER_SIZE, 0);
        if (n>0){
            printf("%s\n", buffer);
            if(strcmp(buffer, "Server is full") == 0){
                break;
            }
        }
            
    }
    closesocket(server_socket);
    WSACleanup();
    return 0;
}