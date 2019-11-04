#include "stListenRfcomm.h"

int get_system_output(char* cmd, char **output, int size)
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

