#ifndef __NW_ARM_4G_PRO_H
#define __NW_ARM_4G_PRO_H

#include"stPreDefine.h"
#include"stUartOper.h"
#include"stMakeString.h"
#include"stDecodeString.h"
#include"stDeviceOper.h"
#include "stTimerOper.h"	
#include "stCjsonConf.h"
#include "stListenRfcomm.h"
#include "../lib/rfcomm/stRfcomm.h"

int set_timer_sec(int nu, int sec);
extern void *th_run_timer(void *th);
extern void *th_RDWR(void *th);

#endif

