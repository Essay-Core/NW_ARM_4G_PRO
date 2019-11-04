#include "../lib/cJson/cJSON.h"
#include <stdlib.h>
#include <stdio.h>

extern int getJsStr(char *json_str, const char* ch, char* ret_str);
extern int getJsInt(char *json_str, const char* ch, int *ret_int);

extern int insertJsonStr(char*jsonStr, const char* ch, char* subStr);
