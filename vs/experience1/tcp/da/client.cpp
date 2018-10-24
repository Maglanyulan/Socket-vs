#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include "time.h"

#define MAX_BUFFER 1024
#define DAYTIME_SERVER_PORT 13

int main(void){
    SOCKET connectionFd,sAccep;
    int in,in2;
    char bufout[]="I'm a client";
	int out;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    char timebuffer [MAX_BUFFER +1];

    WSAData wsaData;
    if( WSAStartup( MAKEWORD (2, 2), &wsaData)!=0){
        printf("命令套接字初始化失败\n");
        return -1;
    }//创建服务器端套接口

    connectionFd= socket (AF_INET, SOCK_STREAM, 0);
    if(connectionFd==-1){
        printf("socket error \n");
        WSACleanup();
        return(-1);
    }//创建服务器端套接口失败


    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons (DAYTIME_SERVER_PORT);
    servaddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//服务器端地址

	while(1){
        if((sAccep=connect(connectionFd,(struct sockaddr *)&servaddr, sizeof(servaddr)))==INVALID_SOCKET){
            printf("connect() Failed:%d\n", WSAGetLastError());
            closesocket(sAccep);
        }
    	else if(sAccep >=0){
		    in= recv(connectionFd, timebuffer, MAX_BUFFER, 0);
            timebuffer[in] =0;
            printf("%s\n",timebuffer);

            in2= recv(connectionFd, timebuffer, MAX_BUFFER, 0);
            timebuffer[in] =0;
            printf("%s\n",timebuffer);

            out=send(connectionFd,bufout,sizeof(bufout),0);
            if(out==SOCKET_ERROR){
                printf("send() faild.:%d\n",WSAGetLastError());
                closesocket(sAccep);
            }
            else if(out>0)
            printf("send success");

            closesocket(sAccep);
        }
		closesocket(connectionFd);
        WSACleanup();
	    while(1);
        return 0;
    }
}