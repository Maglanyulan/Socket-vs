#include <stdio.h>
#include <winsock2.h>
#include "time.h"
#include <STDIO.H>  
#include <windows.h> 
#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER 1024
#define DAYTIME_SERVER_PORT 13
#define FILE_NAME_MAX_SIZE 512 //每次读写的大小

int main(void){
    SOCKET connectionFd,sAccep;
    int in,in2;
    char bufout[]="I'm a client";
	int out;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    char timebuffer [MAX_BUFFER +1];
	memset(&timebuffer, 0, sizeof(timebuffer));

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
			return -1;
        }

		in= recv(connectionFd, timebuffer, MAX_BUFFER, 0);
		if(in==SOCKET_ERROR){
           printf("recv() faild.:%d\n",WSAGetLastError());
           closesocket(sAccep);
		   return -1;
        }
        timebuffer[in] =0;
        printf("%s\n",timebuffer);	
		
		out=send(connectionFd,bufout,sizeof(bufout),0);
        if(out==SOCKET_ERROR){
           printf("send() faild.:%d\n",WSAGetLastError());
           closesocket(sAccep);
		   return -1;
        }

        in2= recv(connectionFd, timebuffer, MAX_BUFFER, 0);
		if(in2==SOCKET_ERROR){
           printf("recv() faild.:%d\n",WSAGetLastError());
           closesocket(sAccep);
		   return -1;
        }
        timebuffer[in] =0;
        printf("%s\n",timebuffer);

 //输入文件名 
  char file_name[FILE_NAME_MAX_SIZE+1]; 
  memset(file_name, 0, FILE_NAME_MAX_SIZE+1); 
 
  while(1){
  printf("Please Input File Name On Server: "); 
  scanf("%s", &file_name); 
  
  char buffer[MAX_BUFFER]; 
  memset(buffer, 0, MAX_BUFFER); 
  strncpy(buffer, file_name, strlen(file_name)>MAX_BUFFER ? MAX_BUFFER:strlen(file_name)); 
  
  //向服务器发送文件名 
  if(send(connectionFd, buffer, MAX_BUFFER, 0) < 0) 
  { 
    printf("Send File Name Failed\n"); 
    system("pause"); 
    exit(1); 
  } 
  recv(connectionFd, buffer, MAX_BUFFER, 0);
  if(strcmp(buffer,"Not Found!")==0){ 
	   printf("File is non-existent in server !\n"); 
	   continue;
  }
  //打开文件，准备写入 
  FILE * fp = fopen(file_name, "wb"); //windows下是"wb",表示打开一个只写的二进制文件 
  if(NULL == fp) 
  { 
    printf("File: %s Can Not Open To Write\n", file_name); 
    system("pause"); 
    exit(1); 
  } 
  else
  { 
    memset(buffer, 0, MAX_BUFFER); 
    int length = 0; 
    while ((length = recv(connectionFd, buffer, MAX_BUFFER, 0)) > 0) 
    {  
	  printf("File is: %s \n", buffer); 
      if (fwrite(buffer, sizeof(char), length, fp) < length) 
      { 
        printf("File: %s Write Failed\n", file_name); 
        break; 
      } 
	 
      memset(buffer, 0, MAX_BUFFER); 
    } 
  
    printf("Receive File: %s From Server Successful!\n", file_name); 
  } 

  fclose(fp); 
  closesocket(connectionFd); 
   } 
}
  //释放winsock库 
  WSACleanup(); 
  
  system("pause"); 
  return 0; 
} 