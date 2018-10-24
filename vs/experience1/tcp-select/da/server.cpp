#include"stdio.h"
#include"winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include<process.h> 
#include <memory.h>
#include <map> 

//#include <semaphore.h>

#define MAX_BUFFER 1024
#define DAYTIME_SERVER_PORT 13


int totalSockets = 0; // socket的总数  
SOCKET socketArray[7]; // socket组成的数组， 假设最多有7个socket吧  
  
void addToSocketArr(SOCKET s)     
{  
    socketArray[totalSockets] = s;         
    totalSockets++;   
}  
// 日志打印  
void log(const char *pStr)  
{  
    FILE *fp = fopen("log.txt", "a");  
    fprintf(fp, "log:%s\n", pStr);  
    fclose(fp);  
}  

void workthread(void *arg);

int main(){
	int serverFd; 
	int acceptSocket = 0; 
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
   // memset(&client_addr, 0, sizeof(client_addr));

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
	int maxfd = -1;
    if(serverFd >= maxfd)
        maxfd= serverFd;
	addToSocketArr(serverFd); 

    servaddr.sin_family= AF_INET;
    servaddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(DAYTIME_SERVER_PORT);

	if(bind(serverFd,(struct sockaddr *)&servaddr,sizeof(servaddr))==SOCKET_ERROR){
        printf("bind() Failed:%d\n",WSAGetLastError);
        closesocket(serverFd);
        WSACleanup();
        return 1;
    }

    if(listen(serverFd,7)==SOCKET_ERROR){
        printf("listen()Failed:%d\n",WSAGetLastError());
        closesocket(serverFd);
        WSACleanup();
        return 1;
	}

    // 设置socket为非阻塞模式  
    unsigned long nonBlock = 1;     
    ioctlsocket(serverFd, FIONBIO, &nonBlock);   

    while(1)     
    {  
        // 读集, 要记得清零初始化  
		FD_SET   readSet;
        FD_ZERO(&readSet);   

		//FD_SET(serverFd, &readSet); 
		FD_SET   writeSet;  
        FD_ZERO(&writeSet);
  
        // 将每个socket都塞入读集， 便于让内核来监测这些socket  
       int i;
        for( i = 0; i < totalSockets; i++)     
        {              
            FD_SET(socketArray[i], &readSet);      
        }  
  
        // 应用程序通知内核来监测读集中的socket, 最后的NULL表示超时时间无限长  
        int total = select(	maxfd+1, &readSet, &writeSet, NULL, NULL);    
        
        // 我们不考虑select失败， 那么程序到这里， 说明读集中必有socket处于"就绪状态"  
        for(i = 0; i <totalSockets; i++)     
        {  
            char szTmp[20] = {0};  
            sprintf(szTmp, "%d", i);  
            log(szTmp);  
  
            if(socketArray[i] == serverFd)  // 对监听的socket进行判断  
            {  
                log("socketArray[i] == serverFd");  
  
                if(FD_ISSET(serverFd, &readSet)) // 如果该socket在可读集中， 则表明有客户端来连接  
                {  
  
                    log("serverFd, socketArray[i] == serverFd");  
  
                    // 接收来自于客户端的connect请求  
                    SOCKADDR_IN addrClient;    
                    int len = sizeof(SOCKADDR);  
        
                    acceptSocket = accept(serverFd,(SOCKADDR*)&addrClient, &len);  

					if(acceptSocket>maxfd)        
					 maxfd = acceptSocket;

                    // 设置为非阻塞模式  
         			log("to send");  
					 char sendBuf[1024] = "Hello";  
					 int a= send(acceptSocket, sendBuf, sizeof(sendBuf), 0); 
                    
				// 添加到socket数组中  
				nonBlock = 1;     
               ioctlsocket(acceptSocket, FIONBIO, &nonBlock);  
                
			   addToSocketArr(acceptSocket);  
                }  

                continue;  
            }  
  
  
            // 注意：上面的serverFd是不负责通信的， 下面的一些socket都是负责通信的socket  

			 if (FD_ISSET(socketArray[i], &readSet)){  
				log("to receive");  
                  char szRecvBuf[1024] = {0};  
                int a=recv(socketArray[i], szRecvBuf, sizeof(szRecvBuf), 0);   
				if(a>0){szRecvBuf[a]=0;
				printf("socketArray[%d] is %d, %s\n", i,socketArray[i], szRecvBuf);}
			}
            // 如果通信socket处于读就绪状态  
		continue;
	 
        } 

    }  
	 closesocket(acceptSocket);
    // 省略了关闭socket等后续操作  
		closesocket(serverFd);
        WSACleanup();
    return 0;  
}


void workthread(void *arg)  
{  
	FD_SET   socketSet;  
    FD_ZERO(&socketSet); 

	struct timeval time;
	time.tv_sec = 100;
	time.tv_usec = 1000;
    
	fd_set    readSet;    
    FD_ZERO(&readSet);   

	fd_set writeSet; 
	FD_ZERO(&writeSet); 

    char buffer[1024]; 
	memset(buffer,0, sizeof(buffer));

	SOCKET fd = (SOCKET) arg;
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
	int a=sizeof(sa);
	getpeername(fd,(sockaddr*)&sa,&a);


    while(1) { 
	//2）将fdSocket的一个拷贝fdRead传给select函数   
		printf("\n接收到连接：(%s)\n",inet_ntoa(sa.sin_addr));
        readSet = socketSet; 
		writeSet=socketSet;

	int   nRetAll = select(0,&readSet,&writeSet,NULL,&time);//若不设置超时则select为阻塞    
      if(nRetAll >0 ){    
            //是否存在客户端的连接请求。    
            if(FD_ISSET(fd ,&readSet))//在readset中会返回已经调用过listen的套接字。    
            {   
                if(socketSet.fd_count < FD_SETSIZE)    
                {    	FD_SET(fd,&socketSet); 
				}
                int nRecv = recv(fd,buffer,1024,0);
                  if(nRecv > 0){    
                        buffer[nRecv] = 0;   
						printf("来自：IP为%s   port为%d /n说%s\n",inet_ntoa(sa.sin_addr),htons(sa.sin_port),buffer ); 
                        printf("\nrecv  %d :  %s", fd,buffer);    
                    }    
             }  

             if(FD_ISSET(fd,&writeSet)) {       //调用send，发送数据。  
                  char buf[]="hello!";   
                  int nRet = send(fd,buf, strlen(buf)+1 ,0);     
                  if(nRet <= 0){
					  if(GetLastError() == WSAEWOULDBLOCK){    
                                //do nothing    
                            }    
                      else  {    
                         FD_CLR(fd,&writeSet);  
						 closesocket(fd);     
                        }     
				   }  
				  else if(nRet > 0) {  
                        printf("\nsend  hello!");  
                        }  
              }   
			 } 
		 else if(nRetAll == 0)    
        {    
            printf("time out!\n");    
        }    
        else    
        {    
            printf("select error!%d\n",WSAGetLastError());    
            Sleep(5000);    
            break;    
        }      
	}  
	printf("%d ：IP:%s   port:%d 退出\n",WSAGetLastError(),inet_ntoa(sa.sin_addr),htons(sa.sin_port));
	FD_CLR(fd,&readSet);
	closesocket(fd);
}