#ifndef __STDECODESIB_H
#define __STDECODESIB_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef struct Mac_msg
{
	unsigned short earfn;//频点号
	unsigned short pci;//小区物理ID
	unsigned short rnti;  //rnti表示空口无线网络标识,范围1-65535
	unsigned short tti;	//tti = sfn|subframe 范围 0-10239，sfn = //tti/10,subfn=tti%10
	short rssi; //参考信号场强
	short rsrp;	//参考信号功率
	short rsrq;//参考信号质量
	unsigned short msgbliten;//有效数据bit长度
	unsigned short crcstat;//PDU解码可信度
	unsigned char *msgaddr;//PDU存放地址
}stMac_msg;

typedef struct CellScan 
{
	unsigned short earfn;//频点号
	unsigned short pci;  //小区物理ID
	uint32 cid;			 //基站识别码
	unsigned short tac;  //基站跟踪区
	short rsrp;			 //参考信号功率
	short rsrq;			 //参考信号质量
	
}stCellScan;

int DecodeSIBMesg();


#endif