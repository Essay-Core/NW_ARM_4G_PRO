//串口相关的头文件
#ifndef __STUARTOPER_H
#define __STUARTOPER_H

#include"stPreDefine.h"

/******************************************************************* 
* 名称：                  sniffer_Open 
* 功能：            打开串口，并初始化相关设置 
* 入口参数：          port       串口号                  
* 出口参数：        正确返回大于0的整数，错误返回为-1 
*******************************************************************/
extern int sniffer_Open(char* port);


/******************************************************************* 
* 名称：                sniffer_Close 
* 功能：                关闭串口并返回串口设备文件描述 
* 入口参数：        fd    :文件描述符     
* 出口参数：        int 	正确返回大于0的整数，错误返回为-1
*******************************************************************/
extern int sniffer_Close(int fd);

/********************************************************************
* 名称：                  UART0_Send
* 功能：                发送数据
* 入口参数：        fd     :文件描述符
*             send_buf    :存放串口发送数据
*             data_len    :一帧数据的个数
* 出口参数：   正确返回为0，错误返回为-1
*******************************************************************/
extern int UART0_Send(int fd, char *send_buf, int data_len);

#endif 
