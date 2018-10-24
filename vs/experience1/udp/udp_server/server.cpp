#include<stdlib.h>
#include<stdio.h>
#include<Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
//服务器端口号为13
#define DEFAULT_PORT 13
#define BUFFER_LENGTH 1024

void main() {
    WSADATA wsadata;
    SOCKET sSocket;//客户地址长度

    int ilen;
    int isend;
    int iRecv;
    char send_buf[]="Hello! I am a server.";
    char recv_buf[BUFFER_LENGTH];//接收数据的缓冲区
    memset(recv_buf,0,sizeof(recv_buf));
    struct sockaddr_in ser,cli;

    printf ("--------------------\n");
    printf ("Server waiting\n");

    if(WSAStartup(MAKEWORD(2, 2),&wsadata)!=0){
        printf("Failed to load Winsock.\n ");
        return;
    }

    sSocket=socket(AF_INET,SOCK_DGRAM,0);
    if(sSocket==INVALID_SOCKET){
        printf("socket() Failed: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    ser.sin_family=AF_INET;
    ser.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    ser.sin_port=htons(DEFAULT_PORT);

    if(bind(sSocket,(struct sockaddr *)&ser,sizeof(ser))==SOCKET_ERROR){
        printf("bind() Failed: %d\n",WSAGetLastError());
        WSACleanup();
        return;
    }
	else{
        ilen=sizeof(cli);

        iRecv=recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(struct sockaddr*)&cli,&ilen);
        if(iRecv==SOCKET_ERROR){
            printf("recvfrom() Failed: %d\n",WSAGetLastError());
            closesocket(sSocket);
            WSACleanup();
            return;
        }
        else if(iRecv==0){
            closesocket(sSocket);
            WSACleanup();
            return;
		}
        else{
            printf("recvfrom():%s\n",recv_buf);
            printf("Accepted client IP: [%s],port: [%d]\n",inet_ntoa(cli. sin_addr),ntohs(cli.sin_port));
        }

        isend=sendto(sSocket,send_buf,sizeof(send_buf),0,(struct sockaddr*)&cli,ilen);
        if(isend==SOCKET_ERROR){
            printf("sendto() Failed: %d\n",WSAGetLastError());
            printf("------------------\n");
            closesocket(sSocket);
            WSACleanup();
            return;
        }
        else if(isend==0){
            closesocket(sSocket);
            WSACleanup();
            return;
        }
        else{
            printf("sendto() succeeded!\n");
            printf("---------------------\n");
        }
        closesocket(sSocket);
        WSACleanup();
    }
}