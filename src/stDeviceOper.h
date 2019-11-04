#ifndef __STDEVICEOPER_H
#define __STDEVICEOPER_H

#include "stPreDefine.h"
#include "stUartOper.h"
#include "stMakeString.h"
#include "stDecodeString.h"
#include "stTimerOper.h"

extern int DEV_CheckDevStatus(STATION_REQ *stationReq,char *result);
extern int DEV_SendScanPara(struct SCAN_PARA *scanPara, char *result);
extern int DEV_SendLocatePara(struct POSITION_PARA *postionPara, char *result);
extern int DEV_DataTranParaConf(struct SC_CFG *scCfg, char *result);
extern int DEV_WorkPara(struct WORK_PARA *workPara, char *result);

#endif 
