#include <stdio.h>
#include <winsock.h>

int main(){
    char buffer[1024] = "";
    char DATA[1024] = "I Hate C";
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
    struct sockaddr_in clnt;
    int len_clnt = sizeof(clnt);
    /*
        Create a socket
    */
    SOCKET clnt_sd = socket(AF_INET, SOCK_STREAM, 0);
    
    SOCKET serverSd = socket(AF_INET, SOCK_STREAM, 0);
    bind(serverSd,(LPSOCKADDR)&serv_addr,sizeof(serv_addr)); 
    listen(serverSd, 5);
    clnt_sd = accept(serverSd,(struct sockaddr*) &clnt,&len_clnt);
    send(clnt_sd,DATA,strlen(DATA),0);
    printf("Sent: %s\n",DATA);
    recv(clnt_sd,buffer,sizeof(buffer),0);
    printf("Received: %s\n",buffer);
    closesocket(serverSd);
    
    return 0;
}