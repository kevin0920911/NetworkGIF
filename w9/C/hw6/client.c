#include <stdio.h>
#include <winsock.h>

int main(){
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
    SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sd, (LPSOCKADDR) &server, sizeof(server));
    /*
        File 
            DEST: alice.jpg
    */
    FILE *file = fopen("alice.jpg", "rb");
    char buffer[1024];
    while(fread(buffer, 1, 1024, file)){
        send(sd, buffer, 1024, 0);
        printf("Send: %s", buffer);
    }
    send(sd, "END", 1024, 0);
    fclose(file);
    closesocket(sd);
}