#include <stdio.h>
#include <winsock.h>

int main(){
    char buffer[1024]="";
    /*
        winsock startup
    */
    WSADATA wsaData;
    WSAStartup(0x101,(LPWSADATA) &wsaData);
    /*
        Server information
            IP:127.0.0.1
            PORT:1234
    */
    SOCKADDR_IN server,client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(1234);
    /*
        Create socket
    */
    SOCKET serversd = socket(AF_INET, SOCK_STREAM, 0);
    bind(serversd, (LPSOCKADDR) &server, sizeof(server));
    listen(serversd, 5);
    SOCKET clientsd = accept(serversd, (LPSOCKADDR)&client, NULL);
    /*
        File
    */
    FILE *file = fopen("bod.txt", "w");
    recv(clientsd,buffer, 1024, 0);
    printf("Receive: %s", buffer);
    fprintf(file, "%s", buffer);
    fclose(file);
    closesocket(clientsd);
}