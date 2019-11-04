#ifndef __STTIMEROPER_H
#define __STTIMEROPER_H

#include"stPreDefine.h"

#include "stPreDefine.h"
#include "stMakeString.h"
#include "stDecodeString.h"
#include "stDeviceOper.h"


extern int set_timer(int sig_type, struct itimerval itv, int sec);
extern int shut_timer(int sig_type, struct itimerval itv);
extern void signal_hander(int sig);

#endif