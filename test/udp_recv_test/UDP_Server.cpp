#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 5588
#define MAXDATASIZE 32*1024*1024

main()
{
	int sockfd;
	struct sockaddr_in server;
	struct sockaddr_in client;
	socklen_t addrlen;
	int num;
	char buf[MAXDATASIZE];

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
	{
		perror("Creatingsocket failed.");
		exit(1);
	}

	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr= htonl (INADDR_ANY);
	
	if(bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Bind()error.");
		exit(1);
	}   

	addrlen=sizeof(client);
	while(1)  
	{
		num =recvfrom(sockfd,buf,MAXDATASIZE,0,(struct sockaddr*)&client,&addrlen);                                   

		if (num < 0)
		{
			perror("recvfrom() error\n");
			exit(1);
		}

		break;
	}
	
	close(sockfd);  
}
