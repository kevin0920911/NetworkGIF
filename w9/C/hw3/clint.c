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
    SOCKET sd = socket(AF_INET, SOCK_DGRAM, 0);
    for (int i=0;i<5;i++){
        sendto(sd,DATA,strlen(DATA),0,(LPSOCKADDR)&serv_addr,sizeof(serv_addr));
        printf("Sent: %s\n",DATA);
    }
    return 0;
}