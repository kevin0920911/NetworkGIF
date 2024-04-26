#include <stdio.h>
#include <winsock.h>

int main(){
    char buffer[1024] = "";
    char DATA[1024] = "[NCYU]";
    /*
        Initial Winsock
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
    SOCKET serverSd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(serverSd,(LPSOCKADDR)&serv_addr,sizeof(serv_addr));
    /*
        Start recv data
    */
    while (TRUE){
        int n = recv(serverSd,buffer,6,0);
        printf("Received: %s (%d byte)\n",buffer,n);
    }
    
    return 0;
}