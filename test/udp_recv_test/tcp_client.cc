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
 
#define MYPORT  8887
#define BUFFER_SIZE 1024
char SERVER_IP[] = "127.0.0.1";
 
 typedef struct stUdpHeader
{
	int size;
	char* data;
	
}stUdpHeader;
 
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
	
    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
	stUdpHeader data = { 0 };
	data.data = (char*)malloc(sizeof(char)*256*1024+4);

	sprintf(data.data, "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
	data.size = strlen(data.data);
	
	int ret = send(sock_cli, (char*)&data, strlen(data.data)+4 ,0); ///发送
    
	free(data.data);	 
    close(sock_cli);
    return 0;
}
