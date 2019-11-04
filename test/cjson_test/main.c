#include "stCjsonConf.h"
#include <stdio.h>
#include <string.h>

typedef struct stConfMsg
{
	char log_file_path[128];
	unsigned int grade;
	unsigned int TIMER1_init;
	unsigned int TIMER2_init;
	unsigned int TIMER3_init;

}stConfMsg;

int main()
{
	printf("Running Main for cjson test\n");
	FILE* fd = fopen("config.ini","rb");
	if(fd == NULL)
	{
		printf("Open conf.ini ERROR path:%s\n", "./");
		return -1;
	}

	char *readConfBuf = (char*)malloc(sizeof(char)*1024);
	stConfMsg *confmsg = (stConfMsg*)malloc(sizeof(stConfMsg));

	int retRead =  fread(readConfBuf,1,1024, fd);
	printf("fread lens:%d,str:%s\n",strlen(readConfBuf), readConfBuf);
	getJsStr(readConfBuf, "log_file_path",confmsg->log_file_path);	
	getJsInt(readConfBuf, "log_grade",&(confmsg->grade));	
	getJsInt(readConfBuf, "TIMER1_init",&(confmsg->TIMER1_init));	
	getJsInt(readConfBuf, "TIMER2_init",&(confmsg->TIMER2_init));	
	getJsInt(readConfBuf, "TIMER3_init",&(confmsg->TIMER3_init));	
	
		printf("log file path:%s\n log grade:%d\n TIMER1_init:%d\n TIMER2_init:%d\n TIMER3_init:%d\n", confmsg->log_file_path, confmsg->grade, confmsg->TIMER1_init, confmsg->TIMER2_init, confmsg->TIMER3_init);

	free(confmsg);
	confmsg = NULL;

	free(readConfBuf);
	readConfBuf = NULL;

	printf("Main BYE!\n");
	return 0;
}
