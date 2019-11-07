/*******************************************************************

*******************************************************************/
#include "NW_ARM_4G_PRO.h"
#include "stRfcomm.h"

//pid
#include<sys/types.h>
#include<sys/wait.h>
#include<stdbool.h>

int global_x = 10;
int global_xNumber = 0;
int global_channel = 24;
int global_isWaiting = 1;
char global_comm[32] = {0};

int g_isExit = 0;
int g_fd = 0;  
int g_blue_status = 0;


//int time_sec1 = 2;
int time_sec2 = 10;
int time_sec3 = 10;

void *th_Listen(void* th);
void *th_RDWR(void *th);
void *th_run_timer(void *th);
void signal_hander(int m);
int set_timer_sec(int nu, int sec);


void *th_Listen(void* thIn)
{
#ifdef TTT	
	int Nu = 3;
	while(Nu)
	{
		g_blue_status = 1;
		system("sudo ./../test/shell_test/kill_pid_bluetoothd.sh");
		g_blue_status = 2;
		system("sudo ./../test/shell_test/init_bluetooth_listen.sh");
		g_blue_status = 1;
		
		if(g_blue_status == -1)
			break;
		
		Nu--;
	}
#endif

/////////////////////////////////////////////////////////////
	//初始化标志位
	bool g_fg_Find_Max_RFCOMM = true;
	bool g_fg_Find_Max_OK = false;
	bool g_fg_Listen_start = false;
	bool g_fg_Connect_Stop = false;
	bool g_fg_Connect_Reconnect = false;
	
	int ctl = 0;
	int dev = 21;
	bdaddr_t addr = {0};
	bacpy(&addr, BDADDR_ANY);
	
	char cmd[128] = {0};
	//查找已存在的端口文件
	global_x = 2;
	sprintf(global_comm,"/dev/rfcomm%d", global_x);
	while(1)
	{
		//判断是否需要退出线程
		if (g_isExit == 1)
		{
			printf("退出线程\n");	
			break;
		}
		
		if(g_fg_Find_Max_RFCOMM)
		{
			//查找已存在的端口文件
			if(access(global_comm, F_OK) != 0)
			{
				//文件不存在
				//printf("file Not EXIST!\n");
				global_xNumber = global_x;
			}
			else 
			{
				//文件已存在
				global_x++;
				sprintf(global_comm,"/dev/rfcomm%d", global_x);
				continue;
			}	
			
			printf("文件已存在!\n");
			g_fg_Find_Max_RFCOMM = false;
			g_fg_Find_Max_OK = true;
		}
		
		if(g_fg_Find_Max_OK)
		{
			//已过滤存在的端口文件，开始监听连接		
			g_fg_Find_Max_OK = false;
			g_fg_Listen_start = true;
		}
		
		if(g_fg_Listen_start)
		{  
			//release_all(ctl);
			//cmd_release(ctl, dev, &addr, 0, NULL);
#ifdef TTT
			sprintf(cmd, "sudo sdptool add --channel=%d SP", global_channel);
			system(cmd);
			printf("sdptool add ok!\n");
			//开始监听连接
			cmd_listen(ctl, 2, &addr, global_channel, NULL);
			printf("cmd_listen return.\n");
			
			/////////////////////////////////////////////////////
#endif	
			global_x++;
			sprintf(cmd, "sudo ./../test/shell_test/kill_pid_bluetoothd.sh %d %d",global_x, global_channel);
			system(cmd);	
			system("sudo ./../test/shell_test/init_bluetooth_listen.sh");

			g_fg_Listen_start = false;
			g_fg_Connect_Stop = true;
		}
		
		if(g_fg_Connect_Stop)
		{
			//连接断开，准备重连
			g_fg_Connect_Stop = false;
			g_fg_Connect_Reconnect = true;
		}
		
		if(g_fg_Connect_Reconnect)
		{
			//重新判断断开文件默认最大值
			g_fg_Connect_Reconnect = false;
			g_fg_Find_Max_RFCOMM = true;
		}
		
		
		usleep(100);
	}

//////////////////////////////////////////////////////////////

	pthread_exit(NULL);
}


void *th_RDWR(void *th)
{
	printf("Running In th_RDWR thread...\n");
	char comm[32] = {0};
	char cmd[32] = {0};
	
	int i = 0;
	int retReadLen = 0;
	int retWriteLen = 0;
	
	char *buf = (char*)malloc(sizeof(char)*256);
	char* recvBuf = (char*)malloc(sizeof(char)*1024);
	char* str = (char*)malloc(sizeof(char)*1024);

	MessageHeader *msgHead = (MessageHeader*)malloc(sizeof(MessageHeader));
//	sprintf(comm,"/dev/rfcomm%d", global_x);
//	sprintf(global_comm, "/dev/rfcomm%d", global_x);
	global_x = 0;
	sprintf(global_comm, "/dev/rfcomm%d", global_x);
	
	//add 2019年11月5日20:01:26
	//定义标志位
	//初始化时，查找标识位为真，即为准备开始查找
	bool isFindRfcommFile = true;
	bool isExistRfcommFile = false;
	bool isOpenRfcomm = false;
	bool isWriteRead = false;
	bool isWriteReadError = false;
	bool isReConnected = false;
	
	while(1)
	{
		//判断是否需要退出线程
		if (g_isExit == 1)
		{
			printf("退出线程\n");	
			break;
		}
		
		if(isFindRfcommFile)
		{	
			//printf("判断相关rfcomm文件是否存在\n");
			//判断是和否为新增文件？
			//判断相关rfcomm文件是否存在
			if(access(global_comm, F_OK) != 0)
			{
				//printf("file Not EXIST!\n");	
				//sprintf(global_comm,"/dev/rfcomm%d", global_x);
				sleep(1);
				continue;
			}
			
			//查找到了相关的文件
			isFindRfcommFile = false;
			isExistRfcommFile = true;
		}
		
		//判断相关rfcomm文件是否存在
		if(isExistRfcommFile)
		{
			printf("存在，即将打开:%s\n",global_comm);
			//存在，即将打开
			//文件存在，开始读写数据
			g_fd = sniffer_Open(global_comm);
			if (g_fd < 0)
			{
				break;
			}
		
			//已将文件打开
			isExistRfcommFile = false;
			isOpenRfcomm = true;
		}
		
		//打开成功，开始读写数据
		if(isOpenRfcomm)
		{	
			printf("打开成功，开始读写数据\n");	
			isOpenRfcomm = false;
			isWriteRead = true;
		}

		if(isWriteRead)
		{
			printf("正在读写数据\n");	
			//value init 
			retWriteLen = 0;
			retReadLen = 0;
			memset(recvBuf, 0, sizeof(char)*1024);
			memset(str, 0, sizeof(char)*1024);
			memset((char*)msgHead, 0, sizeof(MessageHeader));
			
			//read msg head
			retReadLen = readLenData(&g_fd, recvBuf, MSG_HEAD_SIZE);		
			if(retReadLen < 0 )
			{
				//当读写出错时置位真
				isWriteRead = false;
				isWriteReadError = true;
				continue;
			}

			//decode msg head
			DecodeRecvHead(recvBuf, msgHead);
		
			//read msg data 
			retReadLen = readLenData(&g_fd, recvBuf+MSG_HEAD_SIZE, msgHead->msgSize);	
			if(retReadLen < 0 )
			{
				//当读写出错时置位真
				isWriteRead = false;
				isWriteReadError = true;
				continue;
			}

			printf("th_RDWR read data lens:%ld, data:%s\n",strlen(recvBuf), recvBuf);
			SLOG_ST_INFO("th_RDWR read data lens:%d, data:%s\n",strlen(recvBuf), recvBuf);

			//decode recv data
			DecodeRecvData(msgHead, recvBuf, str); 
			
			//write make data
			retWriteLen = writeLenData(&g_fd, str, strlen(str));
			if(retWriteLen < 0 )
			{
				//当读写出错时置位真
				isWriteRead = false;
				isWriteReadError = true;		
				continue;
			}	
			
		}
			
		if(isWriteReadError)
		{
			printf("读写数据出错，准备重连\n");	
			
			sniffer_Close(g_fd);
			sprintf(cmd, "sudo rfcomm release /dev/rfcomm1");
			system(cmd);
			
			//global_x++;
			//sprintf(global_comm, "/dev/rfcomm%d", global_x);
			//printf("change rfcomm:%s\n", global_comm);
			
			isWriteReadError = false;
			isReConnected = true;
		}
		
		if(isReConnected)
		{
			printf("请重新连接\n");	
			isReConnected = false;
			isFindRfcommFile = true;
		}
		
		//判断是否需要退出线程
		if (g_isExit == 1)
		{
			printf("退出线程\n");	
			break;
		}
		
	} 
		
	//free	
	free(msgHead);
	msgHead = NULL;
	
	free(recvBuf);
	recvBuf = NULL;
	
	free(str);
	str = NULL;
	
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

int main(int argc, char **argv) 
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
	
	int ret;
	void  *thread_result;
	char cmd[128] = {0};
	
////////////////////////////////////////////////////////////////////////////	
#ifdef TTTT  
	int ctl = 0;
	int dev = 1;
	bdaddr_t addr = {0};
	bacpy(&addr, BDADDR_ANY);

	sprintf(cmd, "sudo sdptool add --channel=%d SP", global_channel);
	system(cmd);
	printf("sdptool add ok!\n");
	//开始监听连接
	cmd_listen(ctl, dev, &addr, global_channel, NULL);
#endif 
////////////////////////////////////////////////////////////////////////////
			
#ifdef LISTEN    
	pthread_t th_listen = NULL;
	ret = pthread_create(&th_listen, NULL, th_Listen, NULL);
	if(ret != 0)
	{
		perror("pthread_create error");
		SLOG_ST_ERROR("Create th_Listen false!");
		return -2;
	}
	//th_Listen(NULL);
#endif
	
	
//#ifdef RDWRTTT 
	pthread_t th;
	ret = pthread_create(&th, NULL, th_RDWR, NULL);
	if (ret != 0)
	{	
		printf("Create thread false!\n");
		SLOG_ST_ERROR("Create thread false!");
		return -1;
	}
//#endif


#ifdef TIMERTTT
	pthread_t th_timer;
	ret = pthread_create(&th_timer,NULL, th_run_timer, NULL);
	if (ret != 0)
	{
		printf("Create thread false!\n");
    	SLOG_ST_ERROR("Create thread false!");
		return -1;
	}

	pthread_t th2;
	pthread_t th3;
	pthread_create(&th2,NULL, th_run2, NULL);
	pthread_create(&th3,NULL, th_run3, NULL);

#endif

	//char cmd[33] = { 0 };
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

//#ifdef RDWRTTT
	pthread_join(th, &thread_result);
//#endif

#ifdef LISTEN  
	pthread_join(th_listen, &thread_result);
#endif

#ifdef TIMERTTT
	pthread_join(th_timer, &thread_result);
	pthread_join(th2, &thread_result);
	pthread_join(th3, &thread_result);
#endif

	SLOG_ST_INFO("Main BYE!");
	printf("Main BYE!!\n");
	return 0;
}  
