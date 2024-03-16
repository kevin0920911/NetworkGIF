#include <stdio.h>
#include <random>
#include <winsock.h>

char Quote[10][1024]={
    "Always code as if the guy who ends up maintaining your code will be a violent psychopath who knows where you live. (Martin Golding)\n",
    "One man's crappy software is another man's full time job. (Jessica Gaston)\n",
    "If at first you don't succeed, call it version 1.0 (unknown)\n",
    "All programmers are playwrights and all computers are lousy actors. (Anonymous Hack Actor)\n",
    "Any code of your own that you haven't looked at for six or more months might as well have been written by someone else. (Eagleson's law)\n",
    "Commenting your code is like cleaning your bathroom — you never want to do it, but it really does create a more pleasant experience for you and your guests. (Ryan Campbell)\n",
    "In order to understand recursion, one must first understand recursion. (Anonymous)\n",
    "The best thing about a boolean is even if you are wrong, you are only off by a bit.\n",
    "Should array indices start at 0 or 1? My compromise of 0.5 was rejected without, I thought, proper consideration. (Stan Kelly-Bootle)\n",
    "Computers are good at following instructions, but not at reading your mind. (Donald Knuth)\n"
};

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
        
        int random = rand()%10;

        printf("Server Send: %s\n",Quote[random]);
        send(clntSock,Quote[random], strlen(Quote[random]) ,0);

        closesocket(clntSock);
    }
    

    closesocket(servSock);
	WSACleanup();
    return 0;
}