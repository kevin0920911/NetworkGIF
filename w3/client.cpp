#include <iostream>
#include <cstring>
#include <iomanip>
#include <winsock.h>
#include <string>
#define MAX_LINE 1024
using namespace std;

void printService();
int opition(int);
int main(int argc,char** argv){
    // system("chcp 65001");
    int port = 0;
    int resvByte = 1;
    // window socket set up
    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);

    // Open a TCP socket
    SOCKET sd;   
    sd=socket(AF_INET, SOCK_STREAM, 0);

    // Server information 
    struct sockaddr_in serv;
    serv.sin_family       = AF_INET;
    serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
    

    // Service print
    printService();
    cin>>port;
    port = opition(port);
    serv.sin_port= htons(port);



    // message
    string mSend;
    char   mRecv[MAX_LINE];
    connect(sd, (LPSOCKADDR) &serv, sizeof(serv));
    switch (port)
    {
        case 7: //Echo Service
            cout<<"Enter your message:\n";
            cin.ignore();
            getline(cin, mSend);
            send(sd, mSend.c_str(), mSend.size()+1, 0);
            resvByte = recv(sd, mRecv, MAX_LINE, 0);
            break;
        case 9: //Discard Service
            cout<<"Enter your message:\n";
            cin.ignore();
            getline(cin, mSend);
            send(sd, mSend.c_str(), mSend.size()+1, 0);
            break;
        case 13: //Daytime Service
            resvByte = recv(sd, mRecv, MAX_LINE, 0);
            break;
        case 17: //Quote Service
            resvByte = recv(sd, mRecv, MAX_LINE, 0);
            break;
        case 19: //Char Generator Service
            resvByte = recv(sd, mRecv, MAX_LINE, 0);
            break;
        default:
            cerr<<"Invalid Number!\n";
            exit(1);
            break;
    }

    //print result
    cout<<"______________執行結果______________\n";

    
    cout<<"[傳送內容]\n"<< mSend<<endl;
    cout<<"[傳送內容長度]"<< mSend.size()+1<<" Bytes"<<endl;
    cout<<"____________________________________\n";
    cout<<"[回應內容]\n"<< string(mRecv) << endl;
    cout<<"[回應內容長度]"<<resvByte<<" Bytes"<<endl;
    
    closesocket(sd);
    WSACleanup();
    system("pause");
    return 0;
}
void printService(){
    cout <<         "____________________________________\n";
    cout <<         "|    1. Echo       回應模式          |\n" ;
    cout <<         "|    2. Discard    丟棄模式          |\n" ;
    cout <<         "|    3. Daytime    日期與時間模式     |\n";
    cout <<         "|    4. QUOTE      每日一句          |\n";
    cout <<         "|    5. CHARGEN    字元產生器        |\n";
    cout <<         "|___________________________________|\n";
}


int opition(int n){
    switch (n)
    {
        case 1:
            return 7;
            break;
        case 2:
            return 9;
            break;
        case 3:
            return 13;
            break;
        case 4:
            return 17;
            break;
        case 5:
            return 19;
            break;
        default:
            cerr<<"Invalid Number!";
            exit(1);
            break;
    }
}