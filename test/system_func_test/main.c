#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

static int get_system_output(char* cmd, char **output, int size);
int findStrSub(char *buf, char *tmpStr, char *src);
int g_x = 0;
int g_channel= 24;


void *th_Listen(void* th)
{
	//memset(buf, 0, sizeof(buf));
	//get_system_output(cmd, &buf, 1024);
	//printf("systerm result buf:%s\n", buf);

	//sudo adptool add --channel=22 SP
	//sudo rfcomm listen /dev/rfcomm_x 
	//waitiing for connecting...
	//connent
	//open /dev/rfcomm_x
	//read write operation

	char cmd[32] = { 0 };
	char *buf = (char*)malloc(sizeof(char) * 1024);

	char rfcomm_x[16] = {0};
	char fileName[16][32] = {0};
	char tmp[256] = {0};
	int i = 0;
	int ret = 0;

	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "ls /dev/rfcomm*");
	get_system_output(cmd, &buf, 1024);
	if(strlen(buf) == 0)
	{
		printf("NOT FILES name rfcomm* In the /dev/*\n");
		sprintf(rfcomm_x,"rfcomm%d",g_x);
		g_x = 0;
	}
	else
	{

		while(1)
		{
			memset(rfcomm_x, 0, sizeof(rfcomm_x));
			sprintf(rfcomm_x,"rfcomm%d",g_x);

			if(strstr(buf,rfcomm_x) == NULL)
			{
				break;
			}
			else
			{
				g_x++;
			}
		}
	}

	printf("Cannot find %s, build It!\n", rfcomm_x);
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "sudo sdptool add --channel=%d SP", g_channel);
	system(cmd);
	printf("sdptool add ok!\n");

	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "sudo rfcomm listen /dev/rfcomm%d %d", g_x, g_channel);
	system(cmd);	
	
	free(buf);
	buf = NULL;

	pthread_exit(NULL);
}

int main()
{

	pthread_t th = NULL;
	int pret = pthread_create(&th, NULL, th_Listen, NULL);
	if(pret != 0)
	{
		perror("pthread_create error");
		return -2;
	}
	
	void *thRetVal = NULL;
	pthread_join(th, &thRetVal);

	
	return 0;
}

static int get_system_output(char* cmd, char **output, int size)
{
	if(!cmd || size < 0)
	{
		printf("get_system_output Input ERROR\n");
		return -1;
	}

	FILE *fp = NULL;
	fp = popen(cmd, "r");
	fread(*output, 1, 1024, fp);
	pclose(fp);

	return 0;
}

int findStrSub(char *buf, char *tmpStr, char *src)
{
	if(!src)
		return -1;

	char *str1 = strchr(src,'\n');
	if(str1 == NULL)
		return -1;
	
	if(strlen(str1) ==1)
	{
		snprintf(buf,strlen(src),"%s", src);
		return 1;
	}

	int size = strlen(src) - strlen(str1);

	snprintf(buf, size+1,"%s", src);
	strcpy(tmpStr, str1);

	return 0;
}
