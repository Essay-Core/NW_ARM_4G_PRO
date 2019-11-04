
#include "stDecodeString.h"
extern int set_timer_sec(int nu, int sec);
/*******************************************************************
* 名称：              readLenData
* 功能：              readLenData
* 入口参数：         
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int readLenData(int *fd, char *result, int lenIn)
{
	if(fd < 0 || lenIn < 0 || lenIn > 120)
	{
		printf("readLenData ERROR\n");
		return -1;
	}
	printf("Running In readLenData..\n");
	SLOG_ST_DEBUG("Running readLenData...");
	int tmpLen = 0;	
	int retReadLen = 0;
	int recvCount = 0;
	
	char *recvBuf = (char*)malloc(sizeof(char)*lenIn+1);
	memset(recvBuf, 0, sizeof(char)*lenIn+1);	

	while(1)
	{		
		retReadLen = read(*fd, recvBuf+tmpLen, lenIn-tmpLen);
		if(retReadLen < 0)
		{
			printf("read ERROR!\n");
			SLOG_ST_ERROR("read ERROR In readLenData");
			return -1;
		}
		
		tmpLen += retReadLen;
		retReadLen = 0;
		recvCount++;
			
		if(tmpLen >= lenIn || recvCount > 10)
		{
			//printf("read lens:%d, data:%s\n", tmpLen, recvBuf);	
			break;	
		}
	}
	
	memcpy(result, recvBuf, tmpLen);

	free(recvBuf);
	recvBuf = NULL;
	printf("END readLenData!\n");	
	SLOG_ST_DEBUG("End readData.");
	
	return tmpLen;
}


int writeLenData(int *fd, char *str, int lenIn)
{
	if(fd < 0 || str == NULL || lenIn < 0 )
	{
		printf("readLenData ERROR\n");
		return -1;
	}
	printf("Running In writeLenData...\n");
	SLOG_ST_DEBUG("Running In writeLenData...");

	int tmpLen = 0;	
	int retWriteLen = 0;
	int Count = 0;
	
	char *writeBuf = (char*)malloc(sizeof(char)*lenIn+1);
	memcpy(writeBuf, str, strlen(str));

	while(1)
	{		
		retWriteLen = write(*fd, writeBuf+tmpLen, lenIn-tmpLen);
		if(retWriteLen < 0)
		{
			printf("write ERROR!\n");
			SLOG_ST_ERROR("read ERROR In writeLenData!");
			return -1;
		}
		
		tmpLen += retWriteLen;
		retWriteLen = 0;
		Count++;
			
		if(tmpLen >= lenIn || Count > 20)
		{
			break;	
		}
	}
	
	free(writeBuf);
	writeBuf = NULL;
	printf("END writeLenData!\n");
	SLOG_ST_DEBUG("End writeData");
	return tmpLen;
	
}

/*******************************************************************
* 名称：              GetStrToHex
* 功能：              根据大小以及偏移位置截取字段并转为十六进制数
* 入口参数：         
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
UINT32 GetStrToHex(char* cstr, UINT32 size, UINT32 offset)
{
	if(!cstr || size < 0 || offset < 0 || offset > 160)
	{
		printf("GetStrToHex ERROR!\n");
		SLOG_ST_ERROR("GetStrToHex In PARA ERROR! ");
		return -1;
	}
	//printf("GetStrToHex Start..\n");
	char *str = (char*)malloc(sizeof(char)*(size+1));
	UINT32 val = 0;

	snprintf(str, size+1, "%s", cstr+offset);
	sscanf(str, "%x", &val);
	
	free(str);
	//printf("GetStrToHex End!!\n");
	return val;
	
} 


/*******************************************************************
* 名称：              GetStrToStr
* 功能：              GetStrToStr 大小以及偏移位置截取字段
* 入口参数：         
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
UINT32 GetStrToStr(char* cstr, UINT32 size, UINT32 offset, char* result)
{
	if(!cstr || size < 0 || offset < 0 || offset > 256)
	{
		printf("GetStrToHex ERROR!\n");
		SLOG_ST_ERROR("GetStrToHex In Para ERROR");
		return -1;
	}
	
	char *str = (char*)malloc(size+1);
	
	snprintf(str, size+1, "%s", cstr+offset);
	
	strcpy(result, str);
	
	free(str);
	
	return 0;	
} 

/*******************************************************************
* 名称：              DecodeRecvHead
* 功能：              解析头结构体
* 入口参数：         
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int DecodeRecvHead(char* headBufStr, MessageHeader *msgHeadOut)
{
	if(headBufStr == NULL || msgHeadOut == NULL)
	{
		printf("DecodeRecvHead ERROR\n");
		SLOG_ST_ERROR("DecodeRecvHead Input Para ERROR!");
		return -1;
	
	}
	printf("Running In DecodeRecvHead...\n");
	SLOG_ST_DEBUG("Running In DecodeRecvHead...");
	MessageHeader *msgHead = (MessageHeader*)malloc(sizeof(MessageHeader));
			
	msgHead->source = 	GetStrToHex(headBufStr,4, 0);
	msgHead->target = 	GetStrToHex(headBufStr,4, 4);
	msgHead->priority =  	GetStrToHex(headBufStr,4, 8);
	msgHead->Ackflg = 	GetStrToHex(headBufStr,4, 12);
	msgHead->CRC = 		GetStrToHex(headBufStr,4, 16);
	msgHead->msgType = 	GetStrToHex(headBufStr,4, 20);
	msgHead->msgSize = 	GetStrToHex(headBufStr,4, 24);

	if(msgHead->source != MT_PHONE ||  msgHead->target != MT_ARM)
	{
		printf("Msg type ERROR!,source:%d, target:%d\n",msgHead->source, msgHead->target);
		SLOG_ST_ERROR("Msg type ERROR! source:%d, target:%d", msgHead->source, msgHead->target);
		return -1;
	}
	
	memcpy((char*)msgHeadOut, (char*)msgHead, sizeof(MessageHeader));
	free(msgHead);
	printf("End DecodeRecvHead!\n");
	SLOG_ST_DEBUG("End DecodeRecvData.");
	return 0;	
}


/*******************************************************************
* 名称：                  DecodeRecvData
* 功能：               	 解析接收到的数据，头+数据体	 
* 入口参数：         
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int DecodeRecvData(MessageHeader *msgHeadIn, char* cstr, char *stOut)
{
	if (msgHeadIn == NULL || cstr == NULL || strlen(cstr) == 0)
	{
		printf("MakeSendData ILLEGAL ARGUMENT!\n");
		SLOG_ST_ERROR("MakeSendData ILLEGAL ARGUMENT! input str lens:%d data:%s", strlen(cstr), cstr);
		return -1;
	}
	printf("Running In DecodeRecvData...\n");
	SLOG_ST_DEBUG("Running In DecodeRecvData...");

	STATION_REQ 	*stationReq = NULL;
	SCAN_PARA 	*scanPara = NULL;
	POSITION_PARA 	*postionPara = NULL;
	UPDATE_REQ 	*updataReq = NULL;
	SC_CFG 		*scCfg = NULL;
	WORK_PARA 	*workPara = NULL;
	
	char *st = (char*)malloc(sizeof(char)*1024);
	memset(st, 0, sizeof(char)*1024);	
	memset(stOut, 0, sizeof(char)*1024);	

	struct itimerval itv_alrm;
	struct itimerval itv1;
	struct itimerval itv2;
	unsigned int sec1 = 3;
	unsigned int sec2 = 3;

	UINT32 forInt = 0;

	//RECV DATA TYPE	
	printf("RECV DATA TYPE...\n");
	SLOG_ST_INFO("recv data type...");
	switch (msgHeadIn->msgType)
	{
	//#define MT_STATION_REQ 0x11   //查询设备当前状态
	case MT_STATION_REQ:
		printf("The Message type is MT_STATION_REQ!\n");
		SLOG_INFO("The Message type is MT_STATION_REQ.");
		stationReq = (STATION_REQ*)malloc(sizeof(STATION_REQ));
		
		stationReq->AUTO_Switch = GetStrToHex(cstr+MSG_HEAD_SIZE,4, 0);
		//set TIMER3 according to Time_set 			
		stationReq->Time_Set =    GetStrToHex(cstr+MSG_HEAD_SIZE,4, 4);
		printf("stationReq->AUTO_Switch:%d\n", stationReq->AUTO_Switch);
		printf("stationReq->Time_Set:%d\n", stationReq->Time_Set);
		
		//set TIMER3  
		//set_timer(ITIMER_REAL, itv_alrm, stationReq->Time_Set);
		//printf("set TIMER3 ok!\n");
		//SLOG_INFO("set TIMER3 ok!");
		set_timer_sec(2, 10);
		
		memset(st, 0, sizeof(char)*1024);	
		DEV_CheckDevStatus(stationReq, st);		
		memcpy(stOut, st, strlen(st));
		
		free(stationReq);
		stationReq = NULL;
		break;
		
	//#define MT_SCAN_PARA 0x12	//发送扫描配置参数
	case MT_SCAN_PARA:
		printf("The Message type is MT_SCAN_PARA!\n");
		SLOG_INFO("The Message type is MT_SCAN_PARA.");
		scanPara = (SCAN_PARA*)malloc(sizeof(SCAN_PARA));
		scanPara->Plmn = 	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 0);
		scanPara->ScanMode = 	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 4);
		scanPara->Earfnnum = 	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 8);
		
		scanPara->EarfnList = (UINT32*)malloc(sizeof(UINT32)*scanPara->Earfnnum);
		
		for(forInt = 0; forInt < scanPara->Earfnnum; ++forInt)
		{
			scanPara->EarfnList[forInt] = GetStrToHex(cstr+MSG_HEAD_SIZE, 4, 12+forInt*4);
		}
		
		GetStrToStr(cstr+MSG_HEAD_SIZE, 16, 12+scanPara->Earfnnum*4,    scanPara->TelNo);
		GetStrToStr(cstr+MSG_HEAD_SIZE, 16, 12+scanPara->Earfnnum*4+16, scanPara->IMSI);
		GetStrToStr(cstr+MSG_HEAD_SIZE, 16, 12+scanPara->Earfnnum*4+32, scanPara->MMEC);
		GetStrToStr(cstr+MSG_HEAD_SIZE, 16, 12+scanPara->Earfnnum*4+48, scanPara->TMSI);
		
		scanPara->TarMode   = 	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 12+scanPara->Earfnnum*4+64);
		scanPara->StartType = 	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 12+scanPara->Earfnnum*4+68);
		
		printf("scanPara->Plmn:%04x\n", scanPara->Plmn);
		printf("scanPara->ScanMode:%04x\n", scanPara->ScanMode);
		printf("scanPara->Earfnnum:%04x\n", scanPara->Earfnnum);
		
		for(forInt = 0; forInt < scanPara->Earfnnum; ++forInt)
		{
			printf("scanPara->EarfnList[%d]:%04x\n", forInt, scanPara->EarfnList[forInt]);
		}
		
		printf("scanPara->TelNo:%s\n", scanPara->TelNo);
		printf("scanPara->IMSI:%s\n", scanPara->IMSI);
		printf("scanPara->MMEC:%s\n", scanPara->MMEC);
		printf("scanPara->TMSI:%s\n", scanPara->TMSI);
		printf("scanPara->TarMode:%04x\n", scanPara->TarMode);
		printf("scanPara->StartType:%04x\n", scanPara->StartType);
		
		memset(st, 0, sizeof(char)*1024);	
		DEV_SendScanPara(scanPara, st);
		strncpy(stOut, st, strlen(st));
		
		//set TIMER1
		if(scanPara->StartType == 1)
		{
			//TIMER1
			set_timer(ITIMER_VIRTUAL, itv1, sec1);
			printf("set TIMER1 ok!\n");
			SLOG_INFO("set TIMER1 ok.");
		}

		free(scanPara->EarfnList);
		free(scanPara);
		scanPara = NULL;
		
		break;
		
	//#define MT_POSITION_PARA 0x13 //发送定位参数	
	case MT_POSITION_PARA:
		printf("The Message type is MT_POSITION_PARA!\n");
		SLOG_ST_INFO("The Message type is MT_POSITION_PARA!");
		
		postionPara = (POSITION_PARA*)malloc(sizeof(POSITION_PARA));
		
		postionPara->Cell_num = GetStrToHex(cstr+MSG_HEAD_SIZE,4, 0);
		postionPara->cellList = (stCellList*)malloc(postionPara->Cell_num * sizeof(stCellList));
			
		//printf("cstr lens:%d, data:%s, sizeof(stCellList):%d\n",strlen(cstr), cstr, sizeof(stCellList));
		printf("postionPara->Cell_num:%d\n", postionPara->Cell_num);	
		for(forInt = 0; forInt < postionPara->Cell_num; ++forInt)
		{
			postionPara->cellList[forInt].cid =  GetStrToHex(cstr+MSG_HEAD_SIZE, 8, 4+forInt*16+0);
			postionPara->cellList[forInt].pci =  GetStrToHex(cstr+MSG_HEAD_SIZE, 4, 4+forInt*16+8);
			postionPara->cellList[forInt].freq = GetStrToHex(cstr+MSG_HEAD_SIZE, 4, 4+forInt*16+12);	
		
			printf("cellList[%d].cid:%08x\n", forInt, postionPara->cellList[forInt].cid);
			printf("cellList[%d].pci:%04x\n", forInt, postionPara->cellList[forInt].pci);
			printf("cellList[%d].freq:%04x\n",forInt, postionPara->cellList[forInt].freq);
		}
		
		memset(st, 0, sizeof(char)*1024);	
		DEV_SendLocatePara(postionPara, st);
		memcpy(stOut, st, strlen(st));
		
		//TIMER2
		//set_timer(ITIMER_PROF, itv2, sec2);
		//printf("set TIMER2 ok!\n");
		set_timer_sec(2, 10);

		free(postionPara->cellList);
		free(postionPara);
		postionPara = NULL;
		break;
		
	//#define MT_SM_TRIG 0x14	//诱发短信通知
	case MT_SM_TRIG:
		printf("The Message type is MT_SM_TRIG!\n");
		
		break;
		
	//#define MT_UPDATE_REQ 0x15	//无线升级版本应答
	case MT_UPDATE_REQ:
		printf("The Message type is MT_UPDATE_REQ! OK!\n");	
		break;
	
	//#define MT_SOFT_SHUTDOWN 0x16	//软关机命令	
	case MT_SOFT_SHUTDOWN:
		printf("The Message type is MT_SOFT_SHUTDOWN!\n");
		break;
	//#define MT_SC_CFG 0x17	//数传模块参数配置
	case MT_SC_CFG:
		printf("The Message type is MT_SC_CFG!\n");
		SLOG_ST_INFO("The Message type is MT_SC_CFG!");
		scCfg = (SC_CFG*)malloc(sizeof(SC_CFG));
		scCfg->Switch = 	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 0);
		scCfg->Tranfreq = 	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 4);
		scCfg->Rxfreq = 	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 8);
		scCfg->Brate = 		GetStrToHex(cstr+MSG_HEAD_SIZE,4, 12);
		scCfg->PaketLen = 	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 16);
		
		printf("scCfg->Switch:%04x\n", scCfg->Switch);
		printf("scCfg->Tranfreq:%04x\n", scCfg->Tranfreq);
		printf("scCfg->Rxfreq:%04x\n", scCfg->Rxfreq);
		printf("scCfg->Brate:%04x\n", scCfg->Brate);
		printf("scCfg->PaketLen:%04x\n", scCfg->PaketLen);
			
		memset(st, 0, sizeof(char)*1024);	
		//DEV_DataTranParaConf()
			
		free(scCfg);
		scCfg = NULL;
		break;
		
	//#define MT_WORK_PARA 0x18	//全局参数设置(调试用)	
	case MT_WORK_PARA:
		printf("The Message type is MT_WORK_PARA!\n");
		SLOG_ST_INFO("The Message type is MT_WORK_PARA!");

		workPara = (WORK_PARA*)malloc(sizeof(WORK_PARA));
		workPara->SYNC_LEV = 		GetStrToHex(cstr+MSG_HEAD_SIZE,4, 0);
		workPara->SYNC_TIC = 		GetStrToHex(cstr+MSG_HEAD_SIZE,4, 0);
		workPara->Freq_Offset_Lev =	GetStrToHex(cstr+MSG_HEAD_SIZE,4, 0);
		workPara->AGC_Lev = 		GetStrToHex(cstr+MSG_HEAD_SIZE,4, 0);
		
		printf("workPara->SYNC_LEV:%04x\n", workPara->SYNC_LEV);
		printf("workPara->SYNC_TIC:%04x\n", workPara->SYNC_TIC);
		printf("workPara->Freq_Offset_Lev:%04x\n", workPara->Freq_Offset_Lev);
		printf("workPara->AGC_Lev:%04x\n", workPara->AGC_Lev);
		
		memset(st, 0, sizeof(char)*1024);	
		//DEV_WorkPara()
		
		
		free(workPara);
		workPara = NULL;
		break;
                              
	default:
		printf("MakeSendData ILLEGAL TYPE!\n");
		SLOG_ST_ERROR("MakeSendData ILLEGAL TYPE!");
		break; 
	}
	
	printf("End DecodeRecvData!\n");
	SLOG_ST_INFO("End DecodeRecvData.");
	free(st);
	st = NULL;
	
	return 0;
}

