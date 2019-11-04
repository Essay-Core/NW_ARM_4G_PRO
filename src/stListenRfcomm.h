#ifndef __STLISTENRFCOMM_H
#define __STLISTENRFCOMM_H
#include "stPreDefine.h"

int get_system_output(char* cmd, char **output, int size);
static int findStrSub(char *buf, char *tmpStr, char *src);

#endif
