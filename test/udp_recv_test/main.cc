#include <stdio.h>   
#include <sys/types.h>   
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <unistd.h>   
#include <errno.h>   
#include <string.h>   
#include <stdlib.h>  
 
#include <time.h> 
#include<sys/time.h>  

#define SERV_PORT   8000   

typedef struct stUdpHeader
{
	int size;
	char* data;
	
}stUdpHeader;

int readLenData(int *sock_fd, char **result, int lenIn ,struct sockaddr_in addr_client)
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
		retReadLen = recvfrom(*sock_fd, recvBuf+tmpLen, lenIn-tmpLen, 0, (struct sockaddr*)&addr_client, (socklen_t *)&len);
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
			//printf("read lens:%d, data:%s\n", tmpLen, recvBuf);	
			break;	
		}
	}
	
	//测试时间结束
	gettimeofday(&endTime,NULL);	
	Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
	Timeuse /= 1000000;
	printf("Timeuse = %f\n",Timeuse);

	memcpy(*result, recvBuf, tmpLen);

	free(recvBuf);
	recvBuf = NULL;
	printf("END readLenData!\n");	
	
	return tmpLen;
}

  
int main()  
{    
  /* sock_fd --- socket文件描述符 创建udp套接字*/  
  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock_fd < 0)  
  {  
    perror("socket");  
    exit(1);  
  } 
   
  /* 将套接字和IP、端口绑定 */  
  struct sockaddr_in addr_serv;  
  memset(&addr_serv, 0, sizeof(struct sockaddr_in));  //每个字节都用0填充
  addr_serv.sin_family = AF_INET;
  addr_serv.sin_port = htons(SERV_PORT);
  addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
  int len = sizeof(addr_serv);  

  if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)
  {
	perror("bind error");
	exit(1);
  }
   
  int recv_num;  
  char recv_buf[256*1024+4] = {0};  
  int size = 0;
  
  struct sockaddr_in addr_client;  
  memset(&addr_client, 0, sizeof(struct sockaddr_in));  //每个字节都用0填充
  
  recv_num = recvfrom(sock_fd, recv_buf, 256, 0, (struct sockaddr*)&addr_client, (socklen_t *)&len);
  printf("recv recv_buf:%s, recv_num:%d\n", recv_buf, recv_num);
  
 // recv_num = readLenData(&sock_fd, (char**)&recv_buf, size+4, addr_client);
 // printf("recv recv_buf:%s\n", recv_buf);

  close(sock_fd);  
  
  return 0;  
  
}

