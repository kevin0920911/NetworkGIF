#include <iostream>
#include <fstream> 
#include <string>
#include <winsock.h>
using namespace std;

int main(){
    char buffer[1024] = "";
    /*
        Initial Winsock
    */
   WSADATA wsadata;
   WSAStartup(0x101, (LPWSADATA) &wsadata);
    /*
        Server information
            IP: 127.0.0.1
            PORT: 1234
    */
    struct sockaddr_in serv_addr, clnt_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    /*
        Create a socket
    */
    SOCKET server_sd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(server_sd, (LPSOCKADDR)&serv_addr, sizeof(serv_addr));
    /*
        Start recv data
    */ 
    ofstream fout("bod.txt", ios::out);
    int n;
    int byte=0;
    while ((n = recv(server_sd, buffer, 1024, 0))  && string(buffer) != "END" && n != SOCKET_ERROR){
        byte += n;
        buffer[n] = '\0';
        printf("Received: %s (%d byte)\n", buffer, n);
        fout << buffer << endl ;
    }
    cout<<"Total byte: "<<byte<<endl;
    fout.close();
    
    return 0;
}