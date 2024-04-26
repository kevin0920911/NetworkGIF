#include <stdio.h>
#include <winsock.h>

int main(){
    char buffer[1024] = "";
    char DATA[1024] = "I Hate C";
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
    SOCKET clnt = socket(AF_INET, SOCK_STREAM, 0);
    connect(clnt,(LPSOCKADDR)&serv_addr,sizeof(serv_addr));
    send(clnt,DATA,strlen(DATA),0);
    printf("Sent: %s\n",DATA);
    recv(clnt,buffer,sizeof(buffer),0);
    printf("Received: %s\n",buffer);
    
    closesocket(clnt);
    return 0;
} 