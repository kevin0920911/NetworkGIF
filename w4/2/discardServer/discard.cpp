#include <stdio.h>
#include <winsock.h>


int main(){
    // Initial winsock
    WSADATA wsadata;
    WSAStartup(0x101,&wsadata);
    char str[100];
    //Create Socket for Server and Client
    SOCKET servSock,clntSock;
    struct sockaddr_in serv,clnt;

    //Initial Server Socket
    servSock = socket(AF_INET,SOCK_STREAM,0);
    //Initial Server Information
    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Get Socket from my host
    bind(servSock, (struct sockaddr *) &serv, sizeof(serv));
    
    //Start Service
    int clnt_len=sizeof(clnt);
    //Waiting for connection
    listen(servSock,5);//Allow 5 people in this queue
    while(1){
        printf("Server waits.\n");

        //Get Connect from client
        clntSock =  accept(servSock, (struct sockaddr *)  &clnt,&clnt_len );
        
        //Receive data from client
        while(1){
            int size = recv(clntSock,str, 100, 0);
            str[size] = '\0';
            if(str[0] == '.'){
                break;
            }
            
            printf("Server recveive:%s\n",str);
        };
        closesocket(clntSock);
    }
    

    closesocket(servSock);
	WSACleanup();
    return 0;
}