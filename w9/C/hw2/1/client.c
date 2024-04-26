#include <stdio.h>
#include <winsock.h>
#include <string.h>

int main(){
    char buffer[1024] = "[NCYU][NCYU][NCYU][NCYU][NCYU][NCYU]";
    /*
        Initialize Winsock
    */
    WSADATA wsadata;
    WSAStartup(0x101, (LPWSADATA) &wsadata);

    /*
        Server information
            IP: 127.0.0.1
            PORT: 1234
    */
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);

    /*
        Create a socket
    */
    SOCKET clnt = socket(AF_INET, SOCK_STREAM, 0);
    connect(clnt, (LPSOCKADDR)&serv_addr, sizeof(serv_addr));
    send(clnt, buffer, strlen(buffer),0);
    printf("Sent: %s\n",buffer);
    return 0;
}