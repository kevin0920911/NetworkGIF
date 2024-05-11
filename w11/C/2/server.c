#include <stdio.h>
#include <winsock.h>
#include <time.h>
#define MAXCLIENT 5
#define BUFFER_SIZE 1024
int main(){
    int client_num = 0;

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
    SOCKET client_socket[MAXCLIENT]={0};

    // Bind the socket
    bind(server_socket, (LPSOCKADDR)&server, sizeof(server));
    listen(server_socket, 5);

    // Check table build
    fd_set writefds,readfds;

    while (TRUE){
        // Clear the socket set
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);

        // Add socket to set
        FD_SET(server_socket, &readfds);

        for (int i = 0; i< MAXCLIENT; i++){
            if (client_socket[i]>0){
                FD_SET(client_socket[i],&writefds);
            }
        }

        // Select the socket
        int activity = select(0, &readfds, &writefds, NULL, NULL);

        // Wake up by select
        if (activity == SOCKET_ERROR){
            printf("Select Error\n");
            exit(1);
        }


        // New connection
        if (FD_ISSET(server_socket, &readfds)){
            struct sockaddr_in client;
            int client_size = sizeof(client);
            SOCKET new_socket = accept(server_socket, (LPSOCKADDR)&client, &client_size);
            printf("New connection: socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(client.sin_addr) , ntohs(client.sin_port));
            for (int i = 0; i< MAXCLIENT; i++){
                if (client_socket[i] == 0){
                    client_socket[i] = new_socket;
                    client_num++;
                    printf("The %d client socket is in cli_sd[%d]\n",client_num,i);
                    break;
                }
            }
        }
        // if client can be written
        for (int i = 0; i< MAXCLIENT; i++){
            if (FD_ISSET(client_socket[i],&writefds)){
                time_t now;
                struct tm *tm_info;
                char time_str[1024];
                time(&now);
                tm_info = localtime(&now);
                strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
                int n = send(client_socket[i], time_str, strlen(time_str)+1, 0);
                printf("Send client[%d]: %s\n", i, time_str);
                if (n == SOCKET_ERROR){
                    int error_code = WSAGetLastError();
                    if (error_code == WSAECONNRESET){
                        // Somebody disconnected
                        printf("Host disconnected unexpectedly\n");
                        closesocket(client_socket[i]);
                        client_socket[i] = 0;
                        client_num--;
                    }
                    else{
                        printf("Send failed\n");
                    }
                }
                if (n == 0){
                    printf("Host disconnected\n");
                    closesocket(client_socket[i]);
                    client_socket[i] = 0;
                    client_num--;
                }
            }
        }
        Sleep(1000);
    }
    
    return 0;
}