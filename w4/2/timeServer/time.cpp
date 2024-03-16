#include <stdio.h>
#include <winsock.h>
#include "time.h"

int main(){
    
    // Initial winsock
    WSADATA wsadata;
    WSAStartup(0x101,&wsadata);

    //Create Socket for Server and Client
    SOCKET servSock,clntSock;
    struct sockaddr_in serv,clnt;

    //Initial Server Socket
    servSock = socket(AF_INET,SOCK_STREAM,0);
    //Initial Server Information
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Get Socket from my host
    bind(servSock, (struct sockaddr *) &serv, sizeof(serv));
    
    //Start Service
    int clnt_len=sizeof(clnt);
    //Waiting for connection
    listen(servSock,5);//Allow 5 people in this queue
    while(1){
        printf("Server waits.\n");

        //Get time
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        
        
        //Get Connect from client
        clntSock =  accept(servSock, (struct sockaddr *)  &clnt,&clnt_len );
        
        printf("Server Send:%s\n",asctime(timeinfo));
        send(clntSock,asctime(timeinfo), strlen(asctime(timeinfo)) + 1 ,0);
        closesocket(clntSock);
    }
    

    closesocket(servSock);
	WSACleanup();
    return 0;
}