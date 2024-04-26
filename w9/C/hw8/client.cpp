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
    struct sockaddr_in serv_addr,clint_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);

    clint_addr.sin_family = AF_INET;
    clint_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clint_addr.sin_port = htons(3456);
    /*
        Create a socket
    */
    SOCKET sd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sd, (LPSOCKADDR)&clint_addr, sizeof(clint_addr));
    connect(sd, (LPSOCKADDR)&serv_addr, sizeof(serv_addr));
    /*
        Send data
    */
    ifstream fin("alice.txt");
    string s;
    int byte = 0;
    while ( getline(fin,s) ){
        send(sd,s.c_str(),s.size(),0);
        byte += s.size();
        cout << "Sent: " << s << endl;
        Sleep(1000);
    }
    send(sd,"END",s.size(),0);
    send(sd,to_string(byte).c_str(),to_string(byte).size(),0);
    fin.close();
    closesocket(sd);
    return 0;
}