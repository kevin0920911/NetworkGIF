#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 50
const int PORT[] = {8888, 5678, 5679, 5680};
struct sockaddr_in serverAddr;
SOCKET sd;
void recvThread();

int main(){
    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(0x101, &wsaData);

    /*
        Crete Socket connect(UDP) to server
    */
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    BOOL broadcast = TRUE;
    if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)) == -1){
        printf("Error in setting Broadcast option");
        closesocket(sd);
        WSACleanup();
        return 0;
    }

    /*
        Server Information
            BOARDSERVER
                PORT:
                    8888 (list of boards)
                    5678 (channel 1)
                    5679 (channel 2)
                    5680 (channel 3)
    */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = 0;
    serverAddr.sin_port = htons(PORT[0]);
    if (bind(sd, (LPSOCKADDR)&serverAddr, sizeof(serverAddr)) == -1){
        printf("Error in binding");
        closesocket(sd);
        WSACleanup();
        return 0;
    }
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)recvThread,NULL, 0, NULL);
    int port = 8888; 
    while(scanf("%d", &port)){
        closesocket(sd);
        sd = socket(AF_INET, SOCK_DGRAM, 0);
        if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)) == -1){
            printf("Error in setting Broadcast option");
            closesocket(sd);
            WSACleanup();
            return 0;
        }

        switch (port)
        {
        case 5678:
            printf("SWITCHING TO PORT %d\n", port);
            serverAddr.sin_port = htons(PORT[1]);
            if (bind(sd, (LPSOCKADDR)&serverAddr, sizeof(serverAddr)) == -1){
                printf("Error in binding");
                closesocket(sd);
                WSACleanup();
                return 0;
            }
            break;
        case 5679:
            printf("SWITCHING TO PORT %d\n", port);
            serverAddr.sin_port = htons(PORT[2]);
            if (bind(sd, (LPSOCKADDR)&serverAddr, sizeof(serverAddr)) == -1){
                printf("Error in binding");
                closesocket(sd);
                WSACleanup();
                return 0;
            }
            break;
        case 5680:
            printf("SWITCHING TO PORT %d\n", port);
            serverAddr.sin_port = htons(PORT[3]);
            if (bind(sd, (LPSOCKADDR)&serverAddr, sizeof(serverAddr)) == -1){
                printf("Error in binding");
                closesocket(sd);
                WSACleanup();
                return 0;
            }
            break;
        default:
            printf("INVALID PORT\n");
            printf("Switching to PORT 8888\n");
            serverAddr.sin_port = htons(PORT[0]);
            if (bind(sd, (LPSOCKADDR)&serverAddr, sizeof(serverAddr)) == -1){
                printf("Error in binding");
                closesocket(sd);
                WSACleanup();
                return 0;
            }
            break;
        }
    }
}

void recvThread(){
    int serverAddrLen = sizeof(serverAddr);
    char message[MAXLINE];
    while (TRUE){
        int n = recvfrom(sd, message, MAXLINE, 0, (LPSOCKADDR)&serverAddr, &serverAddrLen);
        if (n < 0) continue;
        message[n] = '\0';
        printf("Received: %s\n", message);
        Sleep(500);
    }
}