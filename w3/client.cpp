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
    cout<<"______________���浲�G______________\n";

    
    cout<<"[�ǰe���e]\n"<< mSend<<endl;
    cout<<"[�ǰe���e����]"<< mSend.size()+1<<" Bytes"<<endl;
    cout<<"____________________________________\n";
    cout<<"[�^�����e]\n"<< string(mRecv) << endl;
    cout<<"[�^�����e����]"<<resvByte<<" Bytes"<<endl;
    
    closesocket(sd);
    WSACleanup();
    system("pause");
    return 0;
}
void printService(){
    cout <<         "____________________________________\n";
    cout <<         "|    1. Echo       �^���Ҧ�          |\n" ;
    cout <<         "|    2. Discard    ���Ҧ�          |\n" ;
    cout <<         "|    3. Daytime    ����P�ɶ��Ҧ�     |\n";
    cout <<         "|    4. QUOTE      �C��@�y          |\n";
    cout <<         "|    5. CHARGEN    �r�����;�        |\n";
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