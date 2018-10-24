#include"stdio.h"
#include"winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include"time.h"


#define MAX_BUFFER 1024
#define DAYTIME_SERVER_PORT 13

int main(){
    SOCKET serverFd,connectionFd;
    int  i= 1,out,in;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    char timebuffer[MAX_BUFFER+1];
    char buffer[MAX_BUFFER];
    char buf[]="I'm a server";
    time_t currentTime;
    
	WSADATA wsaData;
    if ( WSAStartup(MAKEWORD(2,2),&wsaData)==SOCKET_ERROR ){
        printf("命令套接口初始化失败\n");
        return(-1);
    }

    serverFd=socket(AF_INET,SOCK_STREAM,0);
    if ( serverFd ==-1 ){
        printf("socket error!\n");
        WSACleanup();
        return -1;
    }

    servaddr.sin_family= AF_INET;
    servaddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(DAYTIME_SERVER_PORT);

	if(bind(serverFd,(struct sockaddr *)&servaddr,sizeof(servaddr))==SOCKET_ERROR){
        printf("bind() Failed:%d\n",WSAGetLastError);
        closesocket(serverFd);
        WSACleanup();
        return 1;
    }

    if(listen(serverFd,5)==SOCKET_ERROR){
        printf("listen()Failed:%d\n",WSAGetLastError());
        closesocket(serverFd);
        WSACleanup();
        return 1;
	}


    while (1){
        connectionFd = accept(serverFd, (struct sockaddr *)NULL, NULL);
		if(connectionFd ==INVALID_SOCKET){
            printf("accept() Failed:%d\n",WSAGetLastError);
            closesocket(connectionFd);
            break;
        }
        else if(connectionFd >=0){
            currentTime =time(NULL);
            sprintf(timebuffer, "%s\n", ctime(&currentTime));
            printf("已有%d个访问者\n",i++);
            send (connectionFd, timebuffer, strlen (timebuffer),0);

			out=send(connectionFd,buf,sizeof(buf),0);
            if(out==SOCKET_ERROR){
                printf("send() faild.:%d\n",WSAGetLastError());
                closesocket(connectionFd);
            }
            else
                printf("send success\n");

	        in= recv(connectionFd, buffer, MAX_BUFFER, 0);
            buffer[in] =0;
            printf("%s\n",buffer); 

            closesocket(connectionFd);
        }

		closesocket(serverFd); 
        WSACleanup(); 
        while(1);
        return 0; 
    }
}