/*******************************************************************

*******************************************************************/
#include "NW_ARM_4G_PRO.h"
#include "stRfcomm.h"

//pid
#include<sys/types.h>
#include<sys/wait.h>

int global_x = 1;
int global_channel = 24;
int global_isWaiting = 1;
char global_comm[32] = {0};

int g_isExit = 0;
int g_fd = 0;  


//int time_sec1 = 2;
int time_sec2 = 10;
int time_sec3 = 10;

void *th_Listen(void* th);
void *th_RDWR(void *th);
void *th_run_timer(void *th);
void signal_hander(int m);

int set_timer_sec(int nu, int sec)
{
	if (sec < 0)
	{
		return -1;
	}
	printf("set_timer_sec: nu:%d, sec:%d\n", nu, sec);
	switch(nu)
	{
		case 2:
			time_sec2 = sec;
			break;
		case 3:
			time_sec3 = sec;
		break;
		default:
			break;
	}
}

void *th_Listen(void* thIn)
{
	char cmd[32] = { 0 };
	char *buf = (char*)malloc(sizeof(char) * 1024);

	char rfcomm_x[16] = {0};
	char comm[16] = {0};
	char tmp[256] = {0};
	int ret = 0;
	FILE *fp = NULL;
	
	int ctl = 0;
	int dev = 1;
	bdaddr_t addr = {0};
	bacpy(&addr, BDADDR_ANY);

	sprintf(comm, "/dev/rfcomm%d", global_x++);
	sprintf(global_comm, "/dev/rfcomm%d", global_x++);
	while(1)
	{
		printf("global_isWaiting = %d\n", global_isWaiting);
		switch (global_isWaiting)
		{
			case 0:
				break;
			//断开状态或是初始状态
			case 1:
				//从rfcomm0开始判断/dev/rfcommX文件是否存在。
				//返回-1表示不存在，即可作为监听的端口文件
				//否则就继续判断下一个文件rfcomm1,2,3,4,5，，，等
				if(access(comm,0)==-1)
				{
					//进入等待连接状态流程
					global_isWaiting = 2;
					break;
				}

				global_x++;
				sprintf(comm, "/dev/rfcomm%d", global_x);
				sprintf(global_comm, "/dev/rfcomm%d", global_x);

				//判断是否需要退出线程
				if (g_isExit == 1)
				{
					break;
				}
				break;

			//等待连接状态
			case 2:
				memset(cmd, 0, sizeof(cmd));
				sprintf(cmd, "sudo sdptool add --channel=%d SP", global_channel);
				system(cmd);
				printf("sdptool add ok!\n");
				//开始监听连接
				cmd_listen(ctl, dev, &addr, 0, NULL);
				
				//监听退出，连接断开，进入状态1
				global_isWaiting = 1;

				//判断是否需要退出线程
				if (g_isExit == 1)
				{
					break;
				}
				break;

			
			default:
				//错误的状态
				printf(" global_isWaiting value ERROR!\n");
				break;

		}
		sleep(1);		
		
	}

	free(buf);
	buf = NULL;

EXIT:
	pthread_exit(NULL);
}


void *th_RDWR(void *th)
{
	printf("Running In th_RDWR thread...\n");
	char comm[32] = {0};
	char cmd[32] = {0};
	char *buf = (char*)malloc(sizeof(char)*256);

	int i = 0;
	int retReadLen = 0;
	int retWriteLen = 0;
	char* recvBuf = (char*)malloc(sizeof(char)*1024);
	char* str = (char*)malloc(sizeof(char)*1024);

	MessageHeader *msgHead = (MessageHeader*)malloc(sizeof(MessageHeader));
	sprintf(comm,"/dev/rfcomm%d", global_x);
	sprintf(global_comm, "/dev/rfcomm%d", global_x);
	printf("In RESTART th_RDWR...\n");

	while(1)
	{
		switch(global_isWaiting)
		{
			case 0:
				printf("global_isWaiting = %d\n", global_isWaiting);
				break;
			case 2:
				printf("global_isWaiting = %d\n", global_isWaiting);
				break;

			//等待连接状态	
			case 1:
				printf("global_isWaiting = %d, global_comm:%s\n", global_isWaiting, global_comm);
				//判断相关rfcomm文件是否存在
				if(access(global_comm, F_OK) != 0)
				{
					printf("file Not EXIST!\n");
					break;
				}

				//文件存在，开始读写数据
				printf("OPEN!!!!!!!!!!!!!!, global_comm:%s\n", global_comm);
				g_fd = sniffer_Open(global_comm);
				if (g_fd < 0)
				{
					printf("Open port failed!, return false!");
					SLOG_ST_ERROR("Open port failed, return %d", g_fd);
					goto EXIT;
				}

				printf("open %s success,start to RDWR...\n", comm);
				SLOG_ST_INFO("Open success, start to read or write..");
				
				for (;;)
				{	
					printf("\nStart running In Main for...\n");	
					SLOG_ST_DEBUG("Start running In Main for...");

					//value init 
					retWriteLen = 0;
					retReadLen = 0;
					memset(recvBuf, 0, sizeof(char)*1024);
					memset(str, 0, sizeof(char)*1024);
					memset((char*)msgHead, 0, sizeof(MessageHeader));
					
					//read msg head
					readLenData(&g_fd, recvBuf, MSG_HEAD_SIZE);		
					
					//decode msg head
					DecodeRecvHead(recvBuf, msgHead);
				
					//read msg data 
					retReadLen = readLenData(&g_fd, recvBuf+MSG_HEAD_SIZE, msgHead->msgSize);	
					printf("th_RDWR read data lens:%ld, data:%s\n",strlen(recvBuf), recvBuf);
					SLOG_ST_INFO("th_RDWR read data lens:%d, data:%s\n",strlen(recvBuf), recvBuf);

					//decode recv data
					DecodeRecvData(msgHead, recvBuf, str); 
					
					//write make data
					retWriteLen = writeLenData(&g_fd, str, strlen(str));
					printf("th_RDWR:write data lens:%d, data:%s\n",retWriteLen, str);			
					
					printf("End Main for, and restart!\n\n");
					SLOG_ST_DEBUG("End Main for, and restart");
					
					//if (global_isWaiting == 1 || g_isExit == 1)
					if (g_isExit == 1)
					{
						sniffer_Close(g_fd);
						printf("closed fd, BYE!!\n");
				
						break;
					}

				}
				break;
			case 3:
				printf("global_isWaiting = %d\n", global_isWaiting);

				break;

			default:
				printf("global_isWaiting = %d\n", global_isWaiting);

				break;
		}
		
		//判断是否需要退出线程
		if (g_isExit == 1)
		{
			break;
		}

		if (global_isWaiting == 0)
		{
			break;
		}
		sleep(2);
		if(++global_x >= 10)
			global_x = 0;

		sprintf(global_comm,"/dev/rfcomm%d", global_x);
	}
	
	
	
	//free	
	free(msgHead);
	msgHead = NULL;
	
	free(recvBuf);
	recvBuf = NULL;
	
	free(str);
	str = NULL;
	

EXIT:
	free(buf);
	buf = NULL;
	pthread_exit("Thread BYE!");

	return (void*)0;
}


void *th_run2(void *th)
{
	char *resultStr = (char*)malloc(sizeof(char)*1024);
	memset(resultStr, 0, sizeof(char)*1024);
	int retWriteLen = 0;

	while(1)
	{
		printf("In th_run2.. sleep %d s\n", time_sec2);
		sleep(time_sec2);
			
		DEV_SendLocatePara(NULL, resultStr);
		retWriteLen = writeLenData(&g_fd, resultStr, strlen(resultStr));
			
		
		if(g_isExit == 1)
		{
			break;
		}
	}

	free(resultStr);
	resultStr = NULL;

}

void *th_run3(void *th)
{
	char *resultStr = (char*)malloc(sizeof(char)*1024);
	memset(resultStr, 0, sizeof(char)*1024);
	int retWriteLen = 0;

	while(1)
	{
		printf("In th_run3.. sleep %d s\n", time_sec3);
		sleep(time_sec3);
		
		DEV_CheckDevStatus(NULL, resultStr);
		retWriteLen = writeLenData(&g_fd, resultStr, strlen(resultStr));	

		if(g_isExit == 1)
		{
			break;
		}
	}

	free(resultStr);
	resultStr = NULL;


}

void *th_run_timer(void *th)
{
	printf("Running thread!\n");
	
	struct itimerval itv1;
	struct itimerval itv2;
	struct itimerval itv3;
	
	signal(SIGALRM, signal_hander);
	signal(SIGVTALRM, signal_hander);
	signal(SIGPROF, signal_hander);
	
	set_timer(ITIMER_REAL, itv1, 0);
	set_timer(ITIMER_VIRTUAL, itv2, 0);
	set_timer(ITIMER_PROF, itv3, 0);

	while(1)
	{
		if (g_isExit == 1)
		{
			shut_timer(ITIMER_REAL, itv1);
			shut_timer(ITIMER_VIRTUAL, itv2);
			shut_timer(ITIMER_PROF, itv3);
			break;
		}
		usleep(100);
	}

	pthread_exit("THREAD bye!!!");
	printf("th_run_timer thread END!\n");
}

void signal_hander(int m)
{	
	if(m < 0)
	{
		printf("ERROR type of the para In signal_hander\n");
		SLOG_ST_ERROR("ERROR type of the para in SIGNAL hander!");
		goto ERROR;
	}
	
	char *resultStr = (char*)malloc(sizeof(char)*1024);
	memset(resultStr, 0, sizeof(char)*1024);
	int retWriteLen = 0;
	
	printf("\nsignal handle... type:%d\n", m);
	switch( m )
	{
		//TIMER1
		case SIGVTALRM:
			printf("get SIGVTALRM...\n");
			SLOG_ST_INFO("get SIGVTALRM");
			
			DEV_SendScanPara(NULL, resultStr);
			retWriteLen = writeLenData(&g_fd, resultStr, strlen(resultStr));
			
			printf("signal_hander write data lens:%d, data:%s\n",retWriteLen, resultStr);			
			SLOG_ST_INFO("signal_hander write data lens:%d, data:%s", retWriteLen, resultStr);
		
			break;
			
		//TIMER2
		case SIGPROF: 
			printf("get SIGPROF...\n");
			SLOG_ST_INFO("get SIGPROF");
			
			DEV_SendLocatePara(NULL, resultStr);
			retWriteLen = writeLenData(&g_fd, resultStr, strlen(resultStr));
			
			printf("signal_hander write data lens:%d, data:%s\n",retWriteLen, resultStr);			
			SLOG_ST_INFO("signal_hander write data lens:%d, data:%s", retWriteLen, resultStr);

			break;
		//TIMER3
		case SIGALRM:
			printf("get SIGALRM...\n");
			SLOG_INFO("get SIGALRM");
			
			DEV_CheckDevStatus(NULL, resultStr);
			retWriteLen = writeLenData(&g_fd, resultStr, strlen(resultStr));
			
			printf("signal_hander write data lens:%d, data:%s\n",retWriteLen, resultStr);			
			SLOG_ST_INFO("signal_hander write data lens:%d, data:%s", retWriteLen, resultStr);
		
			break;
			
		default:
			printf("get DEFAULT!! In signal handle\n");
			break;
	}
	
	free(resultStr);
	resultStr = NULL;
	
ERROR:
	printf("\nsignal handle EXIT!\n");

}	

int main(int argc, char **argv) 
//int main_func()   
{  
	//read config file
	FILE* fd = fopen("config.ini","rb");
	if(fd == NULL)
	{
		printf("Open conf.ini ERROR path:%s\n", "./");
		return -1;
	}

	char *readConfBuf = (char*)malloc(sizeof(char)*1024);
	stConfMsg *confmsg = (stConfMsg*)malloc(sizeof(stConfMsg));

	int retRead =  fread(readConfBuf,1,1024, fd);
	fclose(fd);

	getJsStr(readConfBuf, "log_file_path",confmsg->log_file_path);	
	getJsInt(readConfBuf, "log_grade",&(confmsg->grade));	
	
	//init log
	if (init_logger(confmsg->log_file_path, confmsg->grade) != TRUE)
	{
		printf("init logger failed\n");
		perror("init logger failed");
	
		free(confmsg);
		confmsg = NULL;
		
		free(readConfBuf);
		readConfBuf = NULL;
	
		return -2;
	}

	SLOG_ST_INFO("Create th_RDWR thread success!");
	int ret;
	void  *thread_result;

//#ifdef LISTEN    
    //listen bluetooth connect pthread
	pthread_t th_listen = NULL;
	ret = pthread_create(&th_listen, NULL, th_Listen, NULL);
	if(ret != 0)
	{
		perror("pthread_create error");
		SLOG_ST_ERROR("Create th_Listen false!");
		return -2;
	}
//#endif

#ifdef RDWR 
	//read write pthread
	pthread_t th;
	ret = pthread_create(&th, NULL, th_RDWR, NULL);
	if (ret != 0)
	{	
		printf("Create thread false!\n");
		SLOG_ST_ERROR("Create thread false!");
		return -1;
	}
#endif

#ifdef TIMERTTT
	//timer pthread
	pthread_t th_timer;
	ret = pthread_create(&th_timer,NULL, th_run_timer, NULL);
	if (ret != 0)
	{
		printf("Create thread false!\n");
    	SLOG_ST_ERROR("Create thread false!");
		return -1;
	}

//	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
//	pthread_create(&th1,NULL, th_run1, NULL);
	pthread_create(&th2,NULL, th_run2, NULL);
	pthread_create(&th3,NULL, th_run3, NULL);

#endif

	char cmd[33] = { 0 };
	while (1)
	{
		scanf("%s", cmd);
		if (strcmp(cmd,"q") == 0)
		{
			printf("Quit!!\n");
			g_isExit = 1;
			break;
		}
		usleep(100);
	}

	free(confmsg);
	confmsg = NULL;

	free(readConfBuf);
	readConfBuf = NULL;

			
//#ifdef LISTEN  
	pthread_join(th_listen, &thread_result);
//#endif

#ifdef RDWR
	pthread_join(th, &thread_result);
#endif

#ifdef TIMERTTT
	pthread_join(th_timer, &thread_result);
//	pthread_join(th1, &thread_result);
	pthread_join(th2, &thread_result);
	pthread_join(th3, &thread_result);
#endif

	SLOG_ST_INFO("Main BYE!");
	printf("Main BYE!!\n");
	return 0;
}  

#ifdef TTT
int main()
{
	int ctl = 0;
	int dev = 1;
	bdaddr_t addr = {0};
	bacpy(&addr, BDADDR_ANY);

	pid_t pid, pid_wait;
	int status;
	pid = fork();
	if(pid == -1)
	{
		printf("Error to create new process\n");
		return 0;
	}
	else if(pid == 0)
	{
		printf("Child process...\n");
		//main_func();  
	}
	else
	{
		printf("Parent process!, Child process ID:%d\n", pid);
		printf("bluetooth connect testing...\n");
		
		cmd_listen(ctl, dev, &addr, 0, NULL);
		pid_wait = waitpid(pid, &status, 0);
		printf("Child process %d returned!\n", pid_wait);
	}

	return 0;
}
#endif
