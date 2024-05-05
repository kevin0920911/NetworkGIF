#include <stdio.h>
#include <winsock.h>

int main(){
	FILE *fin, *fout;
	fin = fopen("abc.txt", "r");
	fout = fopen("client.txt","w");

	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv;
	int i,n;
	char str[2048]="";
	
	WSAStartup(0x101,&wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sd, (struct sockaddr *)  &serv,sizeof(serv) );
	printf("Connect to server.\n");
	u_long mode = 1;
    ioctlsocket(sd,FIONBIO,&mode);

	while(1){
		char* c_line = NULL;
  		size_t len = 0;
		int status = getline(&c_line,&len,fin);
		if (status != EOF) {
			send(sd,c_line, strlen(c_line)+1,0);	
			printf("Send: %s\n",c_line);
		}
		else{
			send(sd,"END", 4,0);	
			printf("Send: END\n");
		}
		memset(str,0,sizeof(str));
        n = recv(sd,str, sizeof(str), 0);
        if (n > 0) {
			str[n] = '\0';
			printf("Receive: %s\n",str);
			if (strcmp(str, "END\0") == 0 && status == EOF) {
				break;
			}
			else if (strcmp(str, "END\0") == 0) {
				continue;
			}
			fprintf(fout,"%s",str);
			
		}
		else if (n == 0){
			break;
		}
		Sleep(100);
	}
	closesocket(sd);
	fclose(fin);
	fclose(fout);
	WSACleanup();
	
}