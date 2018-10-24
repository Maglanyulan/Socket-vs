#include"stdio.h"
#include"winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include"time.h"


#define MAX_BUFFER 1024
#define DAYTIME_SERVER_PORT 13
#define FILE_NAME_MAX_SIZE 512 //每次读写的大小

int main(){
    SOCKET serverFd,connectionFd;
    int  i= 1,out,in;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    char timebuffer[MAX_BUFFER+1];
	memset(&timebuffer, 0, sizeof(timebuffer));
    char buffer[MAX_BUFFER];
    memset(&buffer, 0, sizeof(buffer));
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
		printf("等待连接...\n");  
		sockaddr_in remoteAddr ;  
		int nAddrlen = sizeof(remoteAddr);  
        connectionFd = accept(serverFd, (struct sockaddr *)&remoteAddr, &nAddrlen);
		if(connectionFd ==INVALID_SOCKET){
            printf("accept() Failed:%d\n",WSAGetLastError);
            closesocket(connectionFd);
            return -1;
        }

          currentTime =time(NULL);
            sprintf(timebuffer, "%s\n", ctime(&currentTime));
            printf("已有%d个访问者\n",i++);
			out=send (connectionFd, timebuffer, strlen (timebuffer),0);	  
			if(out==SOCKET_ERROR){
                printf("send() faild.:%d\n",WSAGetLastError());
                closesocket(connectionFd);
            }	
			
			in= recv(connectionFd, buffer, MAX_BUFFER, 0);
			if(in==SOCKET_ERROR){
           printf("recv() faild.:%d\n",WSAGetLastError());
           closesocket(connectionFd);
		   return -1;
			 }
            buffer[in] =0;
            printf("%s\n",buffer); 
		out=send(connectionFd,buf,sizeof(buf),0);
            if(out==SOCKET_ERROR){
                printf("send() faild.:%d\n",WSAGetLastError());
                closesocket(connectionFd);
            }


    if (recv(connectionFd, buffer, MAX_BUFFER, 0) < 0) 
    { 
      printf("Server Receive Data Failed!"); 
      break; 
    } 
  
    char file_name[FILE_NAME_MAX_SIZE+1]; 
    memset(file_name, 0, FILE_NAME_MAX_SIZE+1); 
    strncpy(file_name, buffer, strlen(buffer)>FILE_NAME_MAX_SIZE ? FILE_NAME_MAX_SIZE:strlen(buffer)); 
    printf("%s\n", file_name); 
  
    FILE * fp = fopen(file_name, "rb"); //windows下是"rb",表示打开一个只读的二进制文件 
    if (NULL == fp) 
    { 
      printf("File: %s Not Found\n", file_name); 
	  strcpy(buffer, "Not Found!"); 
	  send(connectionFd, buffer, MAX_BUFFER, 0);
    } 
        else
    { 
      memset(buffer, 0, MAX_BUFFER); 
      int length = 0; 
  
      while ((length = fread(buffer, sizeof(char), MAX_BUFFER, fp)) > 0) 
      { 
        if (send(connectionFd, buffer, length, 0) < 0) 
        { 
          printf("Send File: %s Failed\n", file_name); 
          break; 
        } 
        memset(buffer, 0, MAX_BUFFER); 
      } 
  
      fclose(fp); 
      printf("File: %s Transfer Successful!\n", file_name); 
    } 
    closesocket(connectionFd); 
  } 
  
  closesocket(serverFd); 
  //释放winsock库 
  WSACleanup(); 
  return 0; 
} 
