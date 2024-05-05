#include <stdio.h>
#include <winsock.h>
#include <time.h>

int main(){
    FILE *fin, *fout;

	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv;
	int i,n;	

	WSAStartup(0x101,&wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sd, (struct sockaddr *)  &serv,sizeof(serv) );
	printf("Connect to server.\n");

    char fileName[1024];
    printf("Enter file name: ");
    scanf("%s", fileName, sizeof(fileName));
    fin = fopen(fileName, "r");
    if (fin == NULL){
        printf("File not found\n");
        return 1;
    }

    memset(fileName,0,sizeof(fileName));
    printf("Enter exports file name: ");
    scanf("%s", fileName, sizeof(fileName));
    fout = fopen(fileName, "w");
    if (fin == NULL){
        printf("File not found\n");
        return 1;
    }

    u_long mode = 1;
    ioctlsocket(sd,FIONBIO,&mode);

    Sleep(5000);
	
	while(1){
        char* c_line = NULL;
  		size_t len = 0;
		int status = getline(&c_line,&len,fin);
        char buffer[2048] = "";
        if (status == EOF){
            int n = send(sd,"END", 3+1,0);
            if (n == SOCKET_ERROR){
                break;
            }
            printf("Send: %s\n","END");
        }
        else{
            send(sd,c_line, strlen(c_line)+1,0);
            printf("Send: %s\n",c_line);
        }
        free(c_line);
        n = recv(sd,buffer, 2048, 0);
        if (n>0){
            buffer[n] = '\0';
            if (strcmp(buffer,"END") == 0 && status == EOF){
                printf("Received: %s\n",buffer);
                break;
            }
            else if (strcmp(buffer,"END") == 0){
                printf("Received: %s\n",buffer);
                continue;
            }
            else{
                printf("Received: %s\n",buffer);
                fprintf(fout,"%s",buffer);
            }
        }
        else if (n == 0){
            break;
        }
        Sleep(1000);
	}
	closesocket(sd);
    fclose(fin);
    fclose(fout);
	WSACleanup();
	
}