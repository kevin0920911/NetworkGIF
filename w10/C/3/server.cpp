#include <stdio.h>
#include <winsock.h>
#include <vector>
using namespace std;

int main(){
	SOCKET sd;
    vector<SOCKET> clientsd;
	WSADATA wsadata;
	struct sockaddr_in serv,clnt;
	int i,n;
	char str[100]="I love NP!";
	
	WSAStartup(0x101,&wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(sd, (struct sockaddr *) &serv, sizeof(serv));
	
	listen(sd,5);
	int clnt_len=sizeof(clnt);
	printf("Server waits.\n");
	SOCKET clnt_sd =  accept(sd, (struct sockaddr *)  &clnt,&clnt_len );
	printf("Client is connected.\n");	
    clientsd.push_back(clnt_sd);

    u_long mode = 1;
    ioctlsocket(sd,FIONBIO,&mode);

	while(1){
        clnt_sd =  accept(sd, (struct sockaddr *)  &clnt,&clnt_len );
        if (clnt_sd != INVALID_SOCKET){
            clientsd.push_back(clnt_sd);
        }
		vector<int> disconnect;
        for (int i = 0; i<clientsd.size();i++){
            int n = send(clientsd[i],str, strlen(str)+1,0);
			if (n <= 0){
				disconnect.push_back(i);
				printf("Client %d is disconnected.\n",i);
			}
        }
		for (auto i:disconnect){
			closesocket(clientsd[i]);
			clientsd.erase(clientsd.begin()+i);
		}
		printf("(server send): %s\n",str);
		Sleep(1000);
	}
	closesocket(sd);
	for (int i = 0; i<clientsd.size();i++){
        closesocket(clientsd[i]);
    }
	WSACleanup();
	system("pause");
	
}