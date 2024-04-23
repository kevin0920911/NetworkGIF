#include<stdio.h>
#include<winsock.h>
char DATA[100] = "";
int main(){
    /*
        Register winsock
    */
    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);

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
        Server sock binding
    */
    SOCKET sd = socket(AF_INET,SOCK_DGRAM,0);
    bind(sd,(LPSOCKADDR)&serv,sizeof(serv));
    printf("Ready to recv on 12345");

    while (1){
        int n = recv(
            sd,
            DATA,100,0
        );
        printf("recv:%s (%d)\n",DATA,n);
    }
    

    closesocket(sd);
	WSACleanup();
	system("pause");
    return 0;
}