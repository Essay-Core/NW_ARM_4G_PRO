#include "stMakeString.h"


/*******************************************************************
* 名称：              MakeSendHead
* 功能：              拼接数据头
* 入口参数：         
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int MakeSendHead(MessageHeader *msgHead,  char* result, int size)
{
	if(msgHead == NULL || result == NULL || size <= 0)
	{
		printf("msg head OR size ERROR\n");	
		return -1;
	
	}
	printf("Running In MakeSendHead...\n");
		
	//MessageHeader head = { 0 };
	MessageHeader *head = (MessageHeader*)malloc(sizeof(MessageHeader));	
	memcpy((char*)head, (char*)msgHead, sizeof(MessageHeader));
	char *str = (char*)malloc(sizeof(char)*256);	
	
	sprintf(str, "%04x%04x%04x%04x%04x%04x%04x",
		head->source,
		head->target,
		head->Ackflg,
		head->CRC,
		head->priority,
		head->msgType,
		head->msgSize);
	
	strncpy(result, str, strlen(str));
	//printf("MakeSendHead result data:%s\n",result);			
	
	free(head);
	head = NULL;
	free(str);
	str = NULL;
	printf("End MakeSendHead!\n");
	return 0;	
}


/*******************************************************************
* 名称：                  MakeSendData
* 功能：                	 拼接数据头+数据体
* 入口参数：         st：结构体	result:返回的结果， type：拼接类型
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int MakeSendData(void *st, char* result)
{
	if (st == NULL)
	{
		printf("MakeSendData ILLEGAL ARGUMENT!\n");
		return -1;
	}
	printf("Running In MakeSendData...\n");	
	MessageHeader *head = (MessageHeader*)malloc(sizeof(MessageHeader));	
	memcpy((char*)head, (char*)st, MSG_HEAD_SIZE);
	
	char *str = (char*)malloc(sizeof(char)*256);	
	char headStr[256] = { 0 };
	
	int forInt = 0;
	int forTmp = 0;
	stENB_INFO *enbInfo = NULL;
	TARG_INFO *targInfo = NULL;
	STAT_INFO *statInfo = NULL;
	UPDATE_ACK *updateAck = NULL;

	printf("Makeing Send Data head->msgType:%04x\n", head->msgType);
	switch (head->msgType)
	{
	// #define MT_ENB_INFO 0x21	//扫描基站信息上报
	case MT_ENB_INFO:
		enbInfo = (stENB_INFO*)malloc(sizeof(stENB_INFO));	
		memcpy((char*)enbInfo, (char*)st, sizeof(stENB_INFO));
		
		MakeSendHead(&enbInfo->msgHead, headStr, sizeof(headStr));
		
		sprintf(str, "%s%08x%04x%04x",
		headStr,
		enbInfo->Cid_num,
		enbInfo->earfn,
		enbInfo->pci);

		for(forInt = 0; forInt < enbInfo->Cid_num; ++forInt)
		{
			sprintf(str+MSG_HEAD_SIZE+16+forTmp,"%08x%04x%04x%04x",
					enbInfo->cidList->cid,	
					enbInfo->cidList->tac,	
					enbInfo->cidList->resp,	
					enbInfo->cidList->rsrq);
			forTmp += 20*forInt;
		}

		//printf("MT_ENB_INFO string len:%d, data:%s\n",strlen(str), str);
		
		free(enbInfo);
		break;
		
	// #define MT_TARG_INFO 0x22	//目标信息上报	
	case MT_TARG_INFO:
		targInfo = (TARG_INFO*)malloc(sizeof(TARG_INFO));		
		memcpy((char*)targInfo, (char*)st, sizeof(TARG_INFO));
		MakeSendHead(&targInfo->msgHead, headStr, sizeof(headStr));
		
		sprintf(str, "%s%04x%04x%08x%04x%04x%04x%04x%s",
			headStr,  
			targInfo->Earfn,
			targInfo->Pci,
			targInfo->Cid,
			targInfo->Tac,
			targInfo->Rssi,
			targInfo->Distance,
			targInfo->Crnti,
			targInfo->Tmsi);
  
		//printf("MT_TARG_INFO string len:%d, data:%s\n",strlen(str), str);
		free(targInfo);
		break;
		
	// #define MT_STAT_INFO 0x23	//状态信息上报
	case MT_STAT_INFO:
		statInfo = (STAT_INFO*)malloc(sizeof(STAT_INFO));			
		memcpy((char*)statInfo, (char*)st, sizeof(STAT_INFO));
		MakeSendHead(&statInfo->msgHead, headStr, sizeof(headStr));
		
		sprintf(str, "%s%04x%04x%04x%04x%s%08x%04x",
			headStr,
			statInfo->Bt_va,
			statInfo->Tem_val,
			statInfo->Dev_stat,
			statInfo->Ad_stat,
			statInfo->Timestart,
			statInfo->Timework,
			statInfo->Version);
  
		//printf("MT_STAT_INFO string len:%d, data:%s\n",strlen(str), str);
		free(statInfo);
		break;
	// #define MT_UPDATE_ACK 0x24	 //版本升级结果
	case MT_UPDATE_ACK:
		updateAck = (UPDATE_ACK*)malloc(sizeof(UPDATE_ACK));			
		memcpy((char*)&updateAck, (char*)st, sizeof(updateAck));
		MakeSendHead(&updateAck->msgHead, headStr, sizeof(headStr));
		
		sprintf(str, "%s%04x%04x",
			headStr,
			updateAck->Rate,
			updateAck->stat);
	  
		//printf("MT_UPDATE_ACK string len:%d, data:%s\n",strlen(str), str);
		free(updateAck);
		
		break;

	default:
		printf("MakeSendData ILLEGAL TYPE!");
		break;
	}

	strncpy(result, str, strlen(str));
	//printf("result string len:%d, data:%s\n",strlen(result), result);
	
	free(str);
	str = NULL;
	printf("End MakeSendData!\n");
	return 0;
}

/*******************************************************************
* 名称：                  GetStrSize
* 功能：              	获取数据字符串总大小
* 入口参数：         st：结构体	result:返回的结果， type：拼接类型
* 出口参数：        正确返回大于0的整数，错误返回为-1
*******************************************************************/
int GetStrSize(UINT32 type, int Cid_num)
{
	if(type < 0)
	{
		return -1;
	}
	
	switch(type)
	{
		case MT_ENB_INFO:
			return (16+20*Cid_num);	
			
		case MT_TARG_INFO:
			return 32+16;
			
		case MT_STAT_INFO:
			return 16+16+8;
			
		case MT_UPDATE_ACK:
			return 8;
		default:
			return -1;
	} 
	
}


