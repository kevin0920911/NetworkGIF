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
    int clinet_addr_len = sizeof(clnt_addr);
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
    while ((n = recvfrom(server_sd, buffer, 1024, 0,(LPSOCKADDR)&clnt_addr,&clinet_addr_len))  && string(buffer) != "END" && n != SOCKET_ERROR){
        if (clnt_addr.sin_addr.s_addr != inet_addr("127.0.0.1") && clnt_addr.sin_port != htons(3456) ){
            continue;
        }
        byte += n;
        buffer[n] = '\0';
        printf("Received: %s (%d byte)\n", buffer, n);
        fout << buffer << endl ;
    }
    cout<<"Total byte: "<<byte<<endl;
    n= recv(server_sd, buffer, 1024, 0);
    buffer[n] = '\0';
    if (atoi(buffer) == byte)
        cout<<"File is sent successfully"<<endl;
    else
        cout<<"File is not sent successfully"<<endl;
    fout.close();
    
    return 0;
}