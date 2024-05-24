#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 50
const int PORT[] = {8888, 5678, 5679, 5680};
int main(){
    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(0x101, &wsaData);

    /*
        Server information
            BOARDSERVER
                PORT:
                    8888 (list of boards)
                    5678 (channel 1)
                    5679 (channel 2)
                    5680 (channel 3)
    */
    SOCKET server = socket(AF_INET, SOCK_DGRAM, 0);
    BOOL broadcast = TRUE;
    if (setsockopt(server, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)) == -1){
        printf("Error in setting Broadcast option");
        closesocket(server);
        WSACleanup();
        return 0;
    }

    /*
        For Client Information
            *In this case, we use UDP => so we need to use sento() function
    */
    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr("255.255.255.255");
    while (TRUE){
        // SCOPE::PORT 8888
        {    
            clientAddr.sin_port = htons(PORT[0]);
            /*
                list of boards
            */
            char message[MAXLINE]="5678/5679/5680";
            sendto(server, message, strlen(message), 0, (LPSOCKADDR)&clientAddr, sizeof(clientAddr));
            printf("Sent (%d): %s\n",PORT[0], message);
        }

        // SOCPE::PORT 5678
        {
            clientAddr.sin_port = htons(PORT[1]);
            /*
                channel 1
            */
            char message[MAXLINE]="THIS IS 5678";
            sendto(server, message, strlen(message), 0, (LPSOCKADDR)&clientAddr, sizeof(clientAddr));
            printf("Sent (%d): %s\n",PORT[1], message);
        }

        // SCOPE::PORT 5679
        {
            clientAddr.sin_port = htons(PORT[2]);
            /*
                channel 2
            */
            char message[MAXLINE]="THIS IS 5679";
            sendto(server, message, strlen(message), 0, (LPSOCKADDR)&clientAddr, sizeof(clientAddr));
            printf("Sent (%d): %s\n",PORT[2], message);
        }

        // SOCPE::PORT 5680
        {
            clientAddr.sin_port = htons(PORT[3]);
            /*
                channel 3
            */
            char message[MAXLINE]="THIS IS 5680";
            sendto(server, message, strlen(message), 0, (LPSOCKADDR)&clientAddr, sizeof(clientAddr));
            printf("Sent (%d): %s\n",PORT[3], message);
        }
        Sleep(500);
    }
    closesocket(server);
    WSACleanup();
}