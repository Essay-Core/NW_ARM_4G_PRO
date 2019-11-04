#ifndef __STPREDEFINE_H
#define __STPREDEFINE_H

#include <stdio.h>      /*标准输入输出定义*/  
#include <stdlib.h>     /*标准函数库定义*/  
#include <stdint.h>
#include <string.h>

#include <unistd.h>     /*Unix 标准函数定义*/     
#include <fcntl.h>      /*文件控制定义*/  
#include <termios.h>    /*PPSIX 终端控制定义*/  

#include <time.h>
#include <utime.h>

#include <unistd.h>
#include <pthread.h> 
#include <arpa/inet.h>
#include "slog.h"


#include <signal.h>
#include <sys/time.h>

#include <time.h>
#include <utime.h>

extern int set_timer_sec(int nu, int sec);

typedef unsigned int UINT32;

//#define DEV_NAME  "/dev/ttyUSB0"
#define DEV_NAME  "/dev/rfcomm1"
//#define DEV_NAME  "/dev/ttyS4"

#define MSG_HEAD_SIZE 28

//MT --Msggage DEV Type
#define MT_PHONE 	0x01
#define MT_ARM 		0x02
#define MT_DATA_RECV 	0x03
#define MT_DATA_SEND 	0x04
#define MT_FPGA 	0x05
#define MT_MCU 		0x06


//phone to arm 
#define MT_STATION_REQ 0x11 	//查询设备当前状态
#define MT_SCAN_PARA 0x12	//发送扫描配置参数
#define MT_POSITION_PARA 0x13 	//发送定位参数
#define MT_SM_TRIG 0x14		//诱发短信通知
#define MT_UPDATE_REQ 0x15	//无线升级版本应答
#define MT_SOFT_SHUTDOWN 0x16	//软关机命令
#define MT_SC_CFG 0x17		//数传模块参数配置
#define MT_WORK_PARA 0x18	//全局参数设置(调试用)

//arm to phone
#define MT_ENB_INFO 0x21	//扫描基站信息上报
#define MT_TARG_INFO 0x22	//目标信息上报
#define MT_STAT_INFO 0x23	//状态信息上报
#define MT_UPDATE_ACK 0x24	//版本升级结果

//auto switch
#define MT_AUTO_SWITCH_OPEN  0x01
#define MT_AUTO_SWITCH_CLOSE 0x00

//plmn
#define MT_PLMN_YD 46000
#define MT_PLMN_LT 46001
#define MT_PLMN_DX 46011

//start type
#define MT_TIME_START  0x01
#define MT_MATCH_START 0x02
#define MT_MANUAL_START 0x03

//SMinfo
#define MT_INVALID 0x00
#define MT_SENDED 0x01
#define MT_SENDED_OK 0x02
#define MT_SEND_FAILED 0x03

//OpCode
#define MT_INVALID_OPER 0x00
#define MT_WAITING_OPER 0x01
#define MT_DRX_OPER 0x02
#define MT_SHUTDOWN_OPER 0x03

//dev_stat
#define MT_DEV_BREAKDOWN 0x00 
#define MT_DEV_STDBY 0x01
#define MT_DEV_SCAN 0x03
#define MT_DEV_LOCATION 0x04
#define MT_DEV_SUCCESS 0x05
#define MT_DEV_LISTEN 0x06

//AD stat
#define MT_AD_BREAKDOWN 0x00
#define MT_AD_NORMAL 0x01
#define MT_AD_BLUETOOTH_BREAK 0x02
#define MT_AD_DATA_ABNORMAL 0x03
#define MT_AD_WIFI_ABNORMAL 0x04

#pragma pack(1)
//json configure
typedef struct stConfMsg
{
	char log_file_path[128];
	unsigned int grade;
	unsigned int TIMER1_init;
	unsigned int TIMER2_init;
	unsigned int TIMER3_init;

}stConfMsg;


typedef struct MessageHeader
{
	UINT32 source;
	UINT32 target;
	UINT32 priority;
	UINT32 Ackflg;
	UINT32 CRC;
	UINT32 msgType;
	UINT32 msgSize;
}MessageHeader;

typedef struct stCidList
{
	UINT32 cid;
	UINT32 tac;
	UINT32 resp;
	UINT32 rsrq;
}stCidList;

//arm to phone struct
typedef struct stENB_INFO
{
	MessageHeader msgHead;
	UINT32 Cid_num;
	UINT32 earfn;
	UINT32 pci;
	stCidList *cidList;

}stENB_INFO;

typedef struct TARG_INFO
{
	MessageHeader msgHead;
	UINT32 Earfn;
	UINT32 Pci;
	UINT32 Cid;
	UINT32 Tac;
	UINT32 Rssi;
	UINT32 Distance;
	UINT32 Crnti;
	char Tmsi[17];
}TARG_INFO;

typedef struct STAT_INFO
{
	MessageHeader msgHead;
	UINT32 Bt_va;
	UINT32 Tem_val;
	UINT32 Dev_stat;
	UINT32 Ad_stat;
	//struct tm Timestart; //UTC
	char Timestart[17];
	UINT32 Timework;
	UINT32 Version;
}STAT_INFO;

typedef struct UPDATE_ACK
{
	MessageHeader msgHead;
	UINT32 Rate;
	UINT32 stat;
}UPDATE_ACK;
//==arm to phone struct END!
#pragma pack()

//phone to arm struct
typedef struct STATION_REQ
{
	MessageHeader msgHead;
	UINT32 AUTO_Switch;
	UINT32 Time_Set;
}STATION_REQ;

typedef struct SCAN_PARA
{
	MessageHeader msgHead;
	UINT32 Plmn;
	UINT32 ScanMode;
	UINT32 Earfnnum;
	UINT32 *EarfnList;
	char TelNo[17];
	char IMSI[17];
	char MMEC[17];
	char TMSI[17];
	UINT32 TarMode;
	UINT32 StartType;

}SCAN_PARA;


typedef struct stCellList
{
	UINT32 cid; //8
	UINT32 pci; //4
	UINT32 freq; //4
}stCellList;

typedef struct POSITION_PARA
{
	MessageHeader msgHead;
	UINT32 Cell_num;
	stCellList *cellList;

}POSITION_PARA;

typedef struct UPDATE_REQ
{
	MessageHeader msgHead;

}UPDATE_REQ;

typedef struct SOFT_SHUTDOWN
{
	MessageHeader msgHead;
	UINT32 OpCode;
}SOFT_SHUTDOWN;

typedef struct SC_CFG
{
	MessageHeader msgHead;
	UINT32 Switch;
	UINT32 Tranfreq;
	UINT32 Rxfreq;
	UINT32 Brate;
	UINT32 PaketLen;
}SC_CFG;

typedef struct WORK_PARA
{
	MessageHeader msgHead;
	UINT32 SYNC_LEV;
	UINT32 SYNC_TIC;
	UINT32 Freq_Offset_Lev;
	UINT32 AGC_Lev;
}WORK_PARA;
//==phone to arm struct END!

#endif

