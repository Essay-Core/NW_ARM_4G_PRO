#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
 #include <time.h> 
#include<sys/time.h>  

#define SERV_PORT   8000   

typedef struct stUdpHeader
{
	int size;
	char* data;
	
}stUdpHeader;

#define MYPORT  8887
#define QUEUE   20
#define BUFFER_SIZE 1024*256
 
 int readLenData(int *sock_fd, char **result, int lenIn)
{
	if(sock_fd < 0 || lenIn < 0 || lenIn > 120)
	{
		printf("readLenData ERROR\n");
		return -1;
	}
	
	printf("Running In readLenData.. lenIn:%d\n", lenIn);
	
	struct timeval startTime,endTime;
	float Timeuse;
	
	int tmpLen = 0;	
	int retReadLen = 0;
	int recvCount = 0;
	int len = sizeof(sockaddr_in);  
	
	char *recvBuf = (char*)malloc(sizeof(char)*lenIn+1);
	memset(recvBuf, 0, sizeof(char)*lenIn+1);	
	
	//测试时间开始
	gettimeofday(&startTime,NULL);
	
	while(1)
	{
		retReadLen = recv(*sock_fd, recvBuf+tmpLen,lenIn-tmpLen, 0);
		//retReadLen = read(*fd, recvBuf+tmpLen, lenIn-tmpLen);
		if(retReadLen < 0)
		{
			printf("read ERROR!\n");
			return -1;
		}
		
		tmpLen += retReadLen;
		retReadLen = 0;
		recvCount++;
		printf("retReadLen:%d, tmpLen:%d\n",retReadLen, tmpLen);	
		if(tmpLen >= lenIn)
		{
			printf("read lens:%d, data:%s\n", tmpLen, recvBuf);	
			break;	
		}
	}
	
	//测试时间结束
	gettimeofday(&endTime,NULL);	
	Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
	Timeuse /= 1000000;
	printf("Timeuse = %f\n",Timeuse);

	//memcpy(*result, recvBuf, tmpLen);

	free(recvBuf);
	recvBuf = NULL;
	printf("END readLenData!\n");	
	
	return tmpLen;
}


int main()
{
    ///定义sockfd
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
    
    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(MYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    ///bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }
    
    printf("监听%d端口\n",MYPORT);
    ///listen，成功返回0，出错返回-1
    if(listen(server_sockfd,QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }
    
    ///客户端套接字
    char buffer[BUFFER_SIZE];
	memset(buffer,0,sizeof(buffer));
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    
    printf("等待客户端连接\n");
    ///成功返回非负描述字，出错返回-1
    int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn<0)
    {
        perror("connect");
        exit(1);
    }
	
    printf("客户端成功连接\n");
	int lenIn = 0;
    int retLen = recv(conn, (char*)&lenIn, 4,0);
	printf("lenIn:%d", lenIn);
	
	retLen = readLenData(&conn, (char**)&buffer, lenIn);
   
    close(conn);
    close(server_sockfd);
    return 0;
}

