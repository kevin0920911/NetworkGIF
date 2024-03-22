#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>

#define MAXLINE 1024 

int main(){
    /*
        Data which will be send/resv to Proxy
    */
    char  str[MAXLINE];
    /*
        Register Winsock API
        Amd Make Sure Whether WinSock API Can Use
    */
    WSADATA wsadata;
    if (WSAStartup(0x101,(LPWSADATA) &wsadata) != 0) {
        fprintf(stderr,"can't use WinSock DLL\n");
        exit(1);
    }
    /*
        Declare Socket
        And Make Sure TCP socket Could be Use or not
    */
    SOCKET sock;
    if ( (sock=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) {
        fprintf(stderr," can't open TCP socket\n");
        exit(1);
    }
    /*
        Server Information
        ProxyServer
            addr: 127.0.0.1
            port: 1234
    */
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (LPSOCKADDR) &serv, sizeof(serv));
    while(1){
        int byte = recv(sock, str, MAXLINE, 0);
        printf("%s\n",str);
        char sendMessage[2];
        scanf("%c",sendMessage);
        send(sock, sendMessage, strlen(sendMessage)+1, 0);
        if (strcmp(sendMessage,"1") == 0){
            int byte = recv(sock, str, MAXLINE, 0);
            printf("%s\n",str);

            char ipadddr[16];
            scanf("%s",ipadddr);
            ipadddr[strlen(ipadddr)] = '\0';
            send(sock, ipadddr, strlen(ipadddr)+1, 0);

            byte = recv(sock, str, MAXLINE, 0);
            printf("%s\n",str);
        }
        else{
            int byte = recv(sock, str, MAXLINE, 0);
            printf("%s\n",str);
        }
        getc(stdin);
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}