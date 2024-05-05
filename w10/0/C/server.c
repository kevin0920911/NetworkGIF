#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* 字串緩衝區長度 */

int main()
{
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n,i;
  	char  	str[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
   	
  	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// 開啟 UDP socket

   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定 IPPORT_ECHO 為 echo port

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
    	
   	
   	cli_len = sizeof(cli);

    u_long iMode=1;
    ioctlsocket(serv_sd,FIONBIO,&iMode);

   	while (1) {
		n=recvfrom(serv_sd, str, MAXLINE, 0, (LPSOCKADDR) &cli, &cli_len);
		str[n]='\0';
			
		if (n > 0 )
	        printf("Recv: %s\n",str);    	// 顯示從 client 傳來的字串		
	        
		Sleep(1000);
					
		int nError=WSAGetLastError();
		if(nError!=WSAEWOULDBLOCK && nError!=0){
			printf("Disconnected! error code:%d\n",nError);
			closesocket(cli_sd);
			break;
	    }       
    }
 
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	WSACleanup();
}