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
    int port;
    printf("Input the port number u want to recv: ");
    scanf ("%d",&port); 
    serv.sin_port = htons(port);
    serv.sin_family = AF_INET;


    /*
        Client information tmp
    */
    struct sockaddr_in client;
    int len_client = sizeof(client);
    /*
        Server sock binding
    */
    SOCKET sd = socket(AF_INET,SOCK_DGRAM,0);
    bind(sd,(LPSOCKADDR)&serv,sizeof(serv));
    printf("Ready to recv on %d",port);

    for (int i=0;i<10;i++){
        int n = recvfrom(
            sd,
            DATA,100,0,
            (LPSOCKADDR) &client, &len_client
        );
        printf("recv:%s (%d)\n",DATA,n);
    }
    closesocket(sd);
	WSACleanup();
	system("pause");
    return 0;
}