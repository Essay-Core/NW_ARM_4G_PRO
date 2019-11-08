#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>

static int count = 0;
static struct itimerval oldtv;
struct itimerval itv, itv1, itv2, itv3;

int g_flags = 0;
int time_sec1 = 10;
int time_sec2 = 10;
int time_sec3 = 10;

int set_timer(int sig_type, struct itimerval itv, unsigned int sec)
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

	printf("set_timer...\n");
	itv.it_interval.tv_sec = sec;
	itv.it_interval.tv_usec= 0;
	itv.it_value.tv_sec= sec;
	itv.it_value.tv_usec= 0;

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
	itv.it_value.tv_sec= 0;
	itv.it_value.tv_usec= 0;

	setitimer(sig_type, &itv, &oldtv);
	printf("shut_timer EXIT!!\n");

	return 0;
	
}

void signal_hander(int m)
{
	if(m < 0)
	{
		printf("ERROR type of the para In signal_hander\n");
	}

	printf("signal hander...\n");
	count++;
	printf("int m:%d, count:%d\n", m, count);
	switch( m )
	{
		case SIGALRM:
			printf("get SIGALRM...\n");
			break;
		case SIGVTALRM:
			printf("get SIGVTALRM...\n");

			break;
		case SIGPROF: 
			printf("get SIGPROF...\n");

			break;
		default:
			printf("DEFAULT!\n");
			break;
	}

	if(count == 30)
	{
		shut_timer(ITIMER_REAL, itv1);
		shut_timer(ITIMER_VIRTUAL, itv2);
		shut_timer(ITIMER_PROF, itv3);
	}
}	

void *th_run(void *th)
{
	printf("RUNning thread!\n");
	signal(SIGALRM, signal_hander);
	signal(SIGVTALRM, signal_hander);
	signal(SIGPROF, signal_hander);
	unsigned int sec = 1;
	unsigned int sec2 = 3;
	unsigned int sec3 = 5;
	set_timer(ITIMER_REAL, itv1, sec);
	set_timer(ITIMER_VIRTUAL, itv2, sec2);
	set_timer(ITIMER_PROF, itv3, sec3);
	/*
	itv1.it_interval.tv_sec = sec;
	itv1.it_interval.tv_usec= 0;
	itv1.it_value.tv_sec= sec;
	itv1.it_value.tv_usec= 0;
	setitimer(ITIMER_REAL, &itv1, &oldtv);

	itv2.it_interval.tv_sec = sec2;
	itv2.it_interval.tv_usec= 0;
	itv2.it_value.tv_sec= sec2;
	itv2.it_value.tv_usec= 0;
	setitimer(ITIMER_VIRTUAL, &itv2, &oldtv);
	
	itv3.it_interval.tv_sec = sec3;
	itv3.it_interval.tv_usec= 0;
	itv3.it_value.tv_sec= sec3;
	itv3.it_value.tv_usec= 0;
	setitimer(ITIMER_PROF, &itv3, &oldtv);
	*/
	while(1)
	{
		if(g_flags == 1)
		{
			break;
		}
	}

	pthread_exit("THREAD bye!!!");
	printf("RUNning thread END!\n");
}

void *th_run1(void *th)
{
	while(1)
	{
		printf("In th_run1.. sleep %d s\n", time_sec1);
		sleep(time_sec1);
		time_sec2 +=2; 
		if(g_flags == 1)
		{
			break;
		}
	}
}
void *th_run2(void *th)
{
	while(1)
	{
		printf("In th_run2.. sleep %d s\n", time_sec2);
		sleep(time_sec2);
		time_sec3 +=2; 
		if(g_flags == 1)
		{
			break;
		}
	}

}

void *th_run3(void *th)
{
	while(1)
	{
		printf("In th_run3.. sleep %d s\n", time_sec3);
		sleep(time_sec3);
		time_sec1 +=2; 
		if(g_flags == 1)
		{
			break;
		}
	}

}
#ifdef TTT
int main()
{
	printf("Main running...\n");
	
	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
	pthread_create(&th1,NULL, th_run1, NULL);
	pthread_create(&th2,NULL, th_run2, NULL);
	pthread_create(&th3,NULL, th_run3, NULL);
	char cmd[33] = { 0 };

	while(1)
	{
		scanf("%s", cmd);
		if(strcmp((const char*)cmd, "q") == 0)
		{	
			g_flags = 1;
			break;
		}
	}
	void *thread_result;
	pthread_join(th1, &thread_result);
	pthread_join(th2, &thread_result);
	pthread_join(th3, &thread_result);
	printf("Main exit! count:%d\n", count);
	exit(0);
	return 0;
}
#endif

