#ifndef __STDECODESTRING_H
#define __STDECODESTRING_H

#include "stPreDefine.h"
#include "stMakeString.h"
#include "stDecodeString.h"
#include "stDeviceOper.h"
#include "stTimerOper.h"

#include "slog.h"	
/*******************************************************************
* 名称：              readLenData
* 功能：              readLenData
* 入口参数：         
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
extern int readLenData(int *fd, char *result, int lenIn);
extern int writeLenData(int *fd, char *str, int lenIn);

extern int DecodeRecvHead(char* headBufStr, MessageHeader *msgHeadOut);
UINT32 GetStrToHex(char* cstr, UINT32 size, UINT32 offset);
UINT32 GetStrToStr(char* cstr, UINT32 size, UINT32 offset, char* result);

/*******************************************************************
* 名称：                  DecodeRecvHead
* 功能：              
* 入口参数：        
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
extern int DecodeRecvHead(char* headBufStr, MessageHeader *msgHeadOut);
extern int DecodeRecvData(MessageHeader *msgHeadIn, char* cstr, char *st);
#endif 
