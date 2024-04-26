#include <stdio.h>
#include <winsock.h>

int main(){
    /*
        File
            DEST: bod.txt
    */
    FILE *fout = fopen("bod.jpg", "w+b");
    /*
        winsock startup
    */
    WSADATA wsaData;
    WSAStartup(0x101,(LPWSADATA) &wsaData);
    /*
        Server information
            IP: 127.0.0.1
            PORT: 1234
    */
    SOCKADDR_IN server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(1234);
    /*
        Create socket
    */
    SOCKET serversd = socket(AF_INET, SOCK_STREAM, 0);
    bind(serversd, (LPSOCKADDR) &server, sizeof(server));
    listen(serversd, 5);
    SOCKET clientsd = accept(serversd, NULL, NULL);
    char buffer[1024];
    int n;
    while ((n = recv(clientsd, buffer, 1024, 0)) && n>0){
        buffer[n] = '\0';
        if (strcmp(buffer, "END") == 0){
            break;
        }
        fwrite(buffer, 1, 1024, fout);
        printf("Receive: %s", buffer);
    }
    fclose(fout);
    closesocket(clientsd);
    
}