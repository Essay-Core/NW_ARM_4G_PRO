#include "stTimerOper.h"


int set_timer(int sig_type, struct itimerval itv, int sec)
{
	if(sig_type != ITIMER_REAL && sig_type !=ITIMER_VIRTUAL && sig_type != ITIMER_PROF)
	{
		printf("ERROR type of the SIGNAL!!!\n");
		return -1;
	}

	if(sec < 0)
	{
		printf("set_timer ERROR, err SECONDS\n");
		return -2;
	}
	printf("set_timer type:%d, sec:%d\n", sig_type, sec);
	
	itv.it_interval.tv_sec = sec;
	itv.it_interval.tv_usec= 0;
	itv.it_value.tv_sec= sec;
	itv.it_value.tv_usec= 0;
	
	struct itimerval oldtv;
	setitimer(sig_type, &itv, &oldtv);
	
	return 0;
}

int shut_timer(int sig_type, struct itimerval itv)
{
	if(sig_type != ITIMER_REAL && sig_type !=ITIMER_VIRTUAL && sig_type != ITIMER_PROF)
	{
		printf("ERROR type of the SIGNAL!!!\n");
		return -1;
	}

	printf("shut_timer...\n");
	itv.it_interval.tv_sec = 0;
	itv.it_interval.tv_usec= 0;
	itv.it_value.tv_sec= 0;
	itv.it_value.tv_usec= 0;
	
	struct itimerval oldtv;
	setitimer(sig_type, &itv, &oldtv);
	
	printf("shut_timer EXIT!!\n");

	return 0;
	
}



