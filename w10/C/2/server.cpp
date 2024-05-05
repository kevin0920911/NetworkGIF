#include <iostream>
#include <string>
#include <winsock.h>
#include <vector>
#include <time.h>
using namespace std;

int main(){

	SOCKET sd;
	vector<SOCKET> clnt_sd;
	u_long mode = 1;
	WSADATA wsadata;
	struct sockaddr_in serv,clnt1,clnt2;
	int i,n;
	char str[2048];
	
	WSAStartup(0x101,&wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(sd, (struct sockaddr *) &serv, sizeof(serv));
	listen(sd,5);
	
	int clnt_len1=sizeof(clnt1);
	int clnt_len2=sizeof(clnt2);
	printf("Server waits.\n");
	
	time_t start, end;
	end = time(NULL);
	start = time(NULL);

	SOCKET clnt = accept(sd, (struct sockaddr *)  &clnt1,&clnt_len1 );
	printf("Client connected.\n");
	ioctlsocket(clnt,FIONBIO,&mode);
	clnt_sd.push_back(clnt);

	clnt = accept(sd, (struct sockaddr *)  &clnt1,&clnt_len1 );
	printf("Client connected.\n");
	ioctlsocket(clnt,FIONBIO,&mode);
	clnt_sd.push_back(clnt);
	

	while(1){
		for (int i = 0; i<clnt_sd.size(); i++){
			// Receive from client
			n = recv(clnt_sd[i],str, 2048, 0);
			if (n>0){
				printf("(%i) %s\n",i+1,str);
				for (int j=0; j<clnt_sd.size(); j++){
					if (i==j) continue;
					// Send to other clients
					send(clnt_sd[j],str, strlen(str)+1,0);
				}
			}
			else if (n == 0){
				// Client disconnected
				goto end;
			}
		}
	}
	end:
	closesocket(sd);
	for (int i=0; i<clnt_sd.size(); i++)
		closesocket(clnt_sd[i]);
	WSACleanup();
	
}