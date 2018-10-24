#include<stdio.h>
#include<Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define DEFAULT_PORT 13
#define DATA_BUFFER 1024

void main (){
    WSADATA wsadata;
    SOCKET sclient;
    int ilen;
    int isend;
    int irecv;
    char send_buf[]="Hello! I am a client";
    char recv_buf [DATA_BUFFER];
    memset(recv_buf, 0, sizeof(recv_buf));
    struct sockaddr_in ser;

    if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0){ 
        printf("Failed to load Winsock. \n");
        return;
    }

    ser.sin_family=AF_INET; 
    ser.sin_port=htons(DEFAULT_PORT); 
    ser.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//建立服务器端地址 

    sclient=socket(AF_INET,SOCK_DGRAM,0);//建立客户端数据报套接口 
    if(sclient==INVALID_SOCKET){
        printf("SOCKET() Fai1ed:%d\n",WSAGetLastError());
        WSACleanup();
        return;
    }

    ilen=sizeof(ser);
    isend=sendto(sclient,send_buf,sizeof(send_buf),0,(struct sockaddr*)&ser,ilen);
    if(isend==SOCKET_ERROR){
        printf("sendto() Falled:%d\n",WSAGetLastError());
        closesocket(sclient);
        WSACleanup();
        return;
    }
    else if(isend==0){
        closesocket(sclient);
        WSACleanup();
        return;
	}
    else
    printf("snedto() succeeded.\n");

    irecv=recvfrom(sclient,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser,&ilen);
    if(irecv==SOCKET_ERROR){
        printf("sendto() Falled:%d\n",WSAGetLastError());
        closesocket(sclient);
        WSACleanup();
        return;
    }
    else if(irecv==0){
        closesocket(sclient);
        WSACleanup();
        return;
    }
    else{
        printf("recvfrom():%s\n",recv_buf);
        printf("------------\n");
    }

    closesocket(sclient);
    WSACleanup();
    }