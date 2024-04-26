#include <iostream>
#include <fstream>
#include <winsock.h>
#include <string> 
using namespace std;

int main(){
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
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    /*
        Create a socket
    */
    SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sd, (LPSOCKADDR)&serv_addr, sizeof(serv_addr));
    /*
        Send data
    */
    ifstream fin("alice.txt");
    string s;
    while ( getline(fin,s) ){
        send(sd,s.c_str(),s.size(),0);
        cout << "Sent: " << s << endl;
        Sleep(1000);
    }
    send(sd,"END",s.size(),0);
    fin.close();
    closesocket(sd);
    return 0;
}