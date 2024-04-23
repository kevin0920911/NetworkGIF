#include <stdio.h>
#include <winsock.h>

char DATA[10][100] = {
                        "\\C is very hard!!!!!!/",
                        "\\Algo is very hard!!!!!!/",
                        "\\NP is very hard!!!!!!/",
                        "\\Information Security is very hard!!!!!!/",
                        "\\Ncat is very hard!!!!!!/",
                        "\\Earn Money is very hard!!!!!!/",
                        "\\Coding is very hard!!!!!!/",
                        "\\Python is very hard!!!!!!/",
                        "\\Life is very hard!!!!!!/",
                        "\\Everthing is very hard!!!!!!/"
                    };

int main(){
    /*
        Register winsock
    */
    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);

    /*
        Client socket => ready to connect to server

        note nate we use UDP, so the socket of client is sock datagram
    */
    SOCKET sd = socket(AF_INET,SOCK_DGRAM,0);


    /*
        Server information
            IP: 127.0.0.1
            Port: 12345
            sinfamily: IPV4
    */
    struct sockaddr_in serv;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(1234);
    serv.sin_family = AF_INET;

    /*
        Start to send data to server
    */
    int n;
    for (int i=0;i<10;i++){
        for (int port=1234;port<1244;port++){
            serv.sin_port = htons(port);
            n = sendto(
                sd,
                DATA[port-1234], strlen(DATA[port-1234]),0,
                (LPSOCKADDR) &serv, sizeof(serv)
            );
            printf("Send: %s (%d)\n",DATA[port-1234],n);
            Sleep(1000);
        }
    }
    
    

    closesocket(sd);
    WSACleanup();
    system("pause");
    return 0;
}