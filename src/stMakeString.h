#ifndef __STMAKESTRING_H
#define __STMAKESTRING_H

#include "stPreDefine.h"


/*******************************************************************
* 名称：                  MakeSendData
* 功能：              拼接字符串
* 入口参数：         st：结构体	result:返回的结果， type：拼接类型
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
extern int MakeSendData(void *st, char* result);

/*******************************************************************
* 名称：                  GetStrSize
* 功能：              
* 入口参数：         st：结构体	result:返回的结果， type：拼接类型
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
extern int GetStrSize(UINT32 type, int Cid_num);

#endif 
