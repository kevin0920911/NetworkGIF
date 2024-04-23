#include <stdio.h>
#include <winsock.h>

char DATA[100] = "\\C is very hard!!!!!!/";
int main(){
    /*
        Register winsock
    */
    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);

    /*
        Client socket => ready to connect to server

        note nate we use UDP, so the socket of client is sock datagram
    */
    SOCKET sd = socket(AF_INET,SOCK_DGRAM,0);


    /*
        Server information
            IP: 127.0.0.1
            Port: 12345
            sinfamily: IPV4
    */
    struct sockaddr_in serv;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(12345);
    serv.sin_family = AF_INET;

    /*
        Start to send data to server
    */
   connect(sd,(LPSOCKADDR) &serv,sizeof(serv));
    int n = send(
        sd,
        DATA, strlen(DATA),0
    );
    printf("Send: %s (%d)\n",DATA,n);

    closesocket(sd);
    WSACleanup();
    system("pause");
    return 0;
}