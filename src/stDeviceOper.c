#include "stDeviceOper.h"

/*******************************************************************
* 名称：                  DEV_CheckDevStatus
* 功能：                  对于设备状态的检查
* 入口参数：       
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int DEV_CheckDevStatus(STATION_REQ * stationReq,char *result)
{	
	if(/*stationReq  == NULL || */result == NULL)
	{
		printf("DEV_CheckDevStatus ERROR\n");
		SLOG_ST_ERROR("DEV_CheckDevStatus Input ERROR");
		return -1;
	}

	MessageHeader *msgHead = (MessageHeader*)malloc(sizeof(MessageHeader));
	STAT_INFO *statInfo = (STAT_INFO*)malloc(sizeof(STAT_INFO));
	char *str = (char*)malloc(sizeof(char)*1024);	
	
	statInfo->Bt_va = 99;
	statInfo->Tem_val = 0x11;
	statInfo->Dev_stat = 0x02;
	statInfo->Ad_stat = 0x03;
	sprintf(statInfo->Timestart, "00000000000000");
	statInfo->Timework = 0x55;
	statInfo->Version = 0x01;
	
	msgHead->source = (0x02);
	msgHead->target = (0x01);
	msgHead->priority = (0x03);
	msgHead->Ackflg = (0x00);
	msgHead->CRC = (0xffff);
	msgHead->msgType = (MT_STAT_INFO);	
	msgHead->msgSize = GetStrSize(msgHead->msgType, 0);	
	memcpy((char*)&statInfo->msgHead, (char*)msgHead, sizeof(MessageHeader));

	memset(str, 0, sizeof(char)*1024);
	memset(result, 0, sizeof(char)*1024);

	MakeSendData(statInfo, str);
	//printf("DEV_CheckDevStatus MakeSendData lens:%d, %s\n",strlen(str),str);
	strncpy(result, str, strlen(str));
	//printf("DEV_CheckDevStatus MakeSendData lens:%d, result:%s\n",strlen(result), result);
	free(str);
	free(msgHead);
	free(statInfo);
	return 0;
}


/*******************************************************************
* 名称：                  DEV_SendScanPara
* 功能：              
* 入口参数：       
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int DEV_SendScanPara(SCAN_PARA *scanPara, char *result)
{	
	if(/*scanPara == NULL || */result == NULL)
	{
		printf("DEV_SendScanPara ERROR\n");
		SLOG_ST_ERROR("DEV_SendScanPara Input ERROR!!");
		return -1;
	}
	printf("Running In DEV_SendScanPara...\n");
	SLOG_ST_INFO("Running In DEV_SendScanPara...");
	MessageHeader *msgHead = (MessageHeader*)malloc(sizeof(MessageHeader));

	stENB_INFO *enbInfo = (stENB_INFO*)malloc(sizeof(stENB_INFO));
	char* buf = (char*)malloc(sizeof(char)*1024);	
	
	enbInfo->Cid_num = (0x01); //1
	enbInfo->earfn = (0xAA);
	enbInfo->pci = (0x0BB);
	
	msgHead->source = (0x02);
	msgHead->target = (0x01);
	msgHead->priority = (0x03);
	msgHead->Ackflg = (0x00);
	msgHead->CRC = (0xffff);
	msgHead->msgType = (MT_ENB_INFO);	
	msgHead->msgSize = GetStrSize(msgHead->msgType, enbInfo->Cid_num);	

	enbInfo->cidList = (stCidList*)malloc(sizeof(stCidList)*enbInfo->Cid_num);
	enbInfo->cidList->cid = 0x01;
	enbInfo->cidList->tac= 0x01;
	enbInfo->cidList->resp = 0x92;
	enbInfo->cidList->rsrq = 0x93;
	
	memcpy((char*)&(enbInfo->msgHead), msgHead, sizeof(MessageHeader));
	
	memset(result, 0, sizeof(char)*1024);	
	memset(buf, 0, sizeof(char)*1024);	
	MakeSendData(enbInfo, buf);	
	memset(result, 0, sizeof(result));	
	memcpy(result, buf, strlen(buf));
	//printf("result:%s\n", result);
		
	free(buf);
	free(enbInfo->cidList);
	free(msgHead);
	free(enbInfo);
	printf("End DEV_SendScanPara!\n");
	SLOG_ST_INFO("End DEV_SendScanPara.");
	return 0;

}


/*******************************************************************
* 名称：                  DEV_SendLocatePara
* 功能：              
* 入口参数：       
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int DEV_SendLocatePara(POSITION_PARA *postionPara, char *result)
{	
	if(/*postionPara == NULL || */result == NULL)
	{
		printf("DEV_SendLocatePara ERROR\n");
		SLOG_ST_ERROR("DEV_SendLocatePara Input ERROR!");
		return -1;
	}
	SLOG_ST_INFO("Running In DEV_SendLocatePara...");
	//向设别通讯，请求的到以下的数据
	MessageHeader *msgHead = (MessageHeader*)malloc(sizeof(MessageHeader));	
	TARG_INFO *targInfo = (TARG_INFO*)malloc(sizeof(TARG_INFO));	
	char* buf = (char*)malloc(sizeof(char)*1024);	

	targInfo->Earfn = 46001;
	targInfo->Pci = 0x11;
	targInfo->Cid = 209340932;
	targInfo->Tac = 9294;
	targInfo->Rssi = 0x44;
	targInfo->Distance = 0x55;
	targInfo->Crnti = 0x66;
	sprintf(targInfo->Tmsi, "0000000000000000");
	
	msgHead->source = (0x02);
	msgHead->target = (0x01);
	msgHead->priority = (0x03);
	msgHead->Ackflg = (0x00);
	msgHead->CRC = (0xffff);
	msgHead->msgType = (MT_TARG_INFO);	
	msgHead->msgSize = GetStrSize(msgHead->msgType, 0);	
	
	memcpy((char*)&targInfo->msgHead, (char*)msgHead, sizeof(MessageHeader));
	memset(buf, 0, sizeof(char)*1024);	

	MakeSendData(targInfo, buf);
	//printf("targInfo Str:%s\n", buf);
	strncpy(result, buf, strlen(buf));
	free(buf);
	free(msgHead);
	free(targInfo);
	SLOG_ST_INFO("End DEV_SendLocatePara.");
	return 0;
}


/*******************************************************************
* 名称：                  DEV_DataTranParaConf
* 功能：              
* 入口参数：       
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int DEV_DataTranParaConf(SC_CFG *scCfg, char *result)
{	
	if(scCfg == NULL || result == NULL)
	{
		printf("DEV_DataTranParaConf ERROR\n");
		SLOG_ST_ERROR("DEV_DataTranParaConf Input ERROR");
		return -1;
	}
	
	return 0;
}


/*******************************************************************
* 名称：                  DEV_UpdateReq
* 功能：              
* 入口参数：       
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int DEV_UpdateReq(UPDATE_REQ *updateReq, char *result)
{
	if(updateReq == NULL || result == NULL)
	{
		printf("DEV_WorkPara ERROR\n");
		SLOG_ST_ERROR("DEV_UpdateReq Input ERROR");
		return -1;
	}
	SLOG_ST_INFO("Running In DEV_UpdateReq...");
	MessageHeader *msgHead = (MessageHeader*)malloc(sizeof(MessageHeader));
	UPDATE_ACK *updateAck = (UPDATE_ACK*)malloc(sizeof(UPDATE_ACK));
	char* buf = (char*)malloc(sizeof(char)*1024);	
		
	updateAck->Rate = 46001;
	updateAck->stat = 0x11;
	
	msgHead->source = (0x01);
	msgHead->target = (0x02);
	msgHead->priority = (0x03);
	msgHead->Ackflg = (0x00);
	msgHead->CRC = (0xffff);
	msgHead->msgType = (MT_UPDATE_ACK);	
	msgHead->msgSize = GetStrSize(msgHead->msgType, 0);	
	memcpy((char*)&updateAck->msgHead, (char*)&msgHead, sizeof(MessageHeader));
	MakeSendData(updateAck, buf);
	
	strncpy(result, buf, strlen(buf));
	
	free(buf);
	free(msgHead);
	free(updateAck);
	SLOG_ST_INFO("End DEV_UpdateReq.");
	
}

/*******************************************************************
* 名称：                  DEV_WorkPara
* 功能：              
* 入口参数：       
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int DEV_WorkPara(WORK_PARA *workPara, char *result)
{	
	if(workPara == NULL || result == NULL)
	{
		printf("DEV_WorkPara ERROR\n");
		SLOG_ST_ERROR("DEV_WorkPara Inout ERROR!!");
		return -1;
	}
	
	return 0;
}


