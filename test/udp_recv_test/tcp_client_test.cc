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


#define MYPORT  5588
#define BUFFER_SIZE 1024*1024*256
char SERVER_IP[] = "192.168.3.100";
 
 typedef struct stUdpHeader
{
	int size;
	char* data;
	
}stUdpHeader;
 
int readLenData(int *sock_fd, char **result, int lenIn);
  
  
int main()
{
    ///定义sockfd
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);  ///服务器ip
    
    printf("连接%s:%d\n",SERVER_IP,MYPORT);
    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
	
    printf("服务器连接成功\n");
	
    int ret =readLenData(&sock_cli, NULL, BUFFER_SIZE);
	
    close(sock_cli);
    return 0;
}

 /*****************************************************************
 *****************************************************************/
int readLenData(int *sock_fd, char **result, int lenIn)
{
	if(sock_fd < 0 || lenIn < 0)
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
		if(retReadLen < 0)
		{
			printf("read ERROR!\n");
			return -1;
		}
		
		tmpLen += retReadLen;
		retReadLen = 0;
		recvCount++;
		if(tmpLen >= lenIn)
		{
			printf("read lens:%d\n", tmpLen);	
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