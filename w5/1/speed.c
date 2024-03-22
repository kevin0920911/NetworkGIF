#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <winsock.h>

#define MAXLINE 1024 

int main(){
    /*
        Data which will be resv from Chargen and Send from Discard Server
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
    SOCKET sd;
    if ( (sd=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) {
        fprintf(stderr," can't open TCP socket\n");
        exit(1);
    }
    /*
        Server Information
        ChargenServ
            addr: 127.0.0.1
            port: 19
        
    */
    struct sockaddr_in ChargenServ;
    ChargenServ.sin_family = AF_INET;
    ChargenServ.sin_addr.s_addr  = inet_addr("127.0.0.1");
    ChargenServ.sin_port = htons(19);

    struct sockaddr_in DiscardServ;
    DiscardServ.sin_family = AF_INET;
    DiscardServ.sin_addr.s_addr  = inet_addr("127.0.0.1");
    DiscardServ.sin_port = htons(9);
    /*
        Start test the Speed of Network
    */
    int byte_count = 0;
    int loopCount = 0;
    time_t start_time, end_time;
    start_time = time(NULL);
    while (loopCount < 10){
        connect(sd, (LPSOCKADDR) &ChargenServ, sizeof(ChargenServ));
        int bytes_received = recv(sd,str,MAXLINE,0);
        if (bytes_received == SOCKET_ERROR){
            fprintf(stderr,"ChargenServ Error\n");
            exit(1);
        }
        connect(sd, (LPSOCKADDR) &DiscardServ, sizeof(DiscardServ));
        int bytes_sent = send(sd, str, bytes_received, 0);
        if (bytes_sent < 0){
            fprintf(stderr,"Discard Server Error\n");
            exit(1);
        }

        byte_count += bytes_sent;
        end_time = time(NULL);
        if (difftime(end_time, start_time) >= 1) {
            printf("Bytes sent to Discard Server: %d\n", byte_count);
            byte_count = 0;
            loopCount ++ ;
            start_time = time(NULL);
        }
    }
    closesocket(sd);
    WSACleanup();
    return 0;
}