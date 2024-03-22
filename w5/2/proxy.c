#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>

#define MAXLINE 1024 

int main(){
    /*
        Data which will be send/resv to DNS Serv and resv from time Server
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
    SOCKET ServSock;
    if ( (ServSock=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) {
        fprintf(stderr," can't open TCP socket\n");
        exit(1);
    }
    /*
        Server Information
        ProxyServer
            addr: 127.0.0.1
            port: 1234
        DateTimeServer
            addr: 127.0.0.1
            port: 13
    */
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct sockaddr_in DateTimeServer;
    DateTimeServer.sin_family = AF_INET;
    DateTimeServer.sin_port = htons(13);
    DateTimeServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    /*
        Bind
    */
    bind(ServSock, (struct sockaddr *) &serv, sizeof(serv));


    struct sockaddr_in client;
    int clnt_len=sizeof(client);
    listen(ServSock,5);
    while(1){
        
        printf("Proxy Server Wait\n");

        /*
            Get Connect from clinet
        */
       SOCKET ClientSock;
       ClientSock =  accept(ServSock, (struct sockaddr *)  &client,&clnt_len );
       while(1){
            char meun[]= "Please enter the Service u want to use\n1)IP Query\n2)Datetime Service\n";
            if (send(ClientSock,meun, strlen(meun)+1,0) == SOCKET_ERROR){
                closesocket(ClientSock);
                break;
            } 
            int size = recv(ClientSock,str, 1024, 0);
            if (size < 0){
                closesocket(ClientSock);
                break;
            }
            str[size] = '\0';
            if (strcmp(str,"1") == 0){
                if (send(ClientSock,"Please enter a IP address\n", strlen("Please enter a IP address\n")+1,0)== SOCKET_ERROR){
                    closesocket(ClientSock);
                    break;
                }

                if (recv(ClientSock,str, 1024, 0)< 0){
                    closesocket(ClientSock);
                    break;
                }
                sscanf(str, "ask://%s", &str);
                LPHOSTENT hp;
                struct in_addr sAddr;
                sAddr.s_addr=inet_addr(str);
                hp= gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr),AF_INET);
                if (hp == NULL){
                    if(send(ClientSock,"NOT FOUND\n",strlen("NOT FOUND\n")+1,0) == SOCKET_ERROR){
                        closesocket(ClientSock);
                        break;
                    }
                }
                else{
                    if(send(ClientSock,hp->h_name,strlen(hp->h_name)+1,0) == SOCKET_ERROR){
                        closesocket(ClientSock);
                        break;
                    }
                }
            }
            else if (strcmp(str,"2") == 0){
                SOCKET ProxySock;
                if ( (ProxySock=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) {
                    fprintf(stderr," can't open TCP socket\n");
                    exit(1);
                }
                connect(ProxySock, (LPSOCKADDR) &DateTimeServer, sizeof(DateTimeServer));
                int size = recv(ProxySock,str, 1024, 0);
                if (size < 0){
                    closesocket(ClientSock);
                    break;
                }
                if(send(ClientSock,str,strlen(str)+1,0) == SOCKET_ERROR){
                    closesocket(ClientSock);
                    break;
                }
                closesocket(ProxySock);
            }
            else{
                if(send(ClientSock,"Invalid data!\n", strlen("Invalid data!\n")+1,0) == SOCKET_ERROR){
                    closesocket(ClientSock);
                    break;
                }
            }
            
       }

       
       closesocket(ClientSock);
    }
}