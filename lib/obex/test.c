#include "openobex/obex.h"
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include "obex_test.h"
#include "obex_test_client.h"
#include "obex_test_server.h"
#include <sys/time.h>

void cb_obex_init(obex_t *handle, obex_object_t *obj,int mode, int enent, int obex_cmd, int obex_rsp);

int read_input(char* answer, size_t size, const char*question, ...)
{
	return 0;
}
#ifdef TS_MAIN
int main()
{
	printf("Start...\n");

	//add
	unsigned int flags = 0;
	bdaddr_t baddr;
	uint8_t channel = 9;
	bacpy(&baddr, BDADDR_ANY);

	struct context global_context = { 0 };

	obex_t *hp = OBEX_Init(OBEX_TRANS_BLUETOOTH,cb_obex_init,flags);
	if(!hp)
	{
		printf("OBEX_Init BLUETOOTH error!\n");
		return -2;
	}
	printf("OBEX_Init sucess!\n");
	
	OBEX_SetUserData(hp, &global_context);
	printf("OBEX_SetUserData sucess!\n");

	struct timeval g_start_time;
	struct timeval g_end_time;
	unsigned long g_timer;
	
	gettimeofday(&g_start_time, NULL);
	printf("timer Start...\n");
	if(BtOBEX_ServerRegister(hp, BDADDR_ANY, channel) < 0)
	{
		perror("BtOBEX_ServerRegister error");
		return -2;
	}
	printf("BtOBEX_ServerRegister sucess!\n");
	

	server_do(hp);
	OBEX_TransportDisconnect(hp);
	gettimeofday(&g_end_time, NULL);
	printf("timer END!!!\n");
	g_timer = 1*1000*1000*(g_end_time.tv_sec-g_start_time.tv_sec)+g_end_time.tv_usec-g_start_time.tv_usec;
	printf("timer = %ld us\n", g_timer);

	return 0;
}//=========Main()============

#endif

void cb_obex_init(obex_t *handle, obex_object_t *obj,int mode, int event, int obex_cmd, int obex_rsp)
{
	printf("cb_obex_init ...\n");
	
	switch(event)
	{
		case OBEX_EV_PROGRESS:
			printf("OBEX_EV_PROGRESS\n");
			break;
		case OBEX_EV_ABORT:
			printf("OBEX_EV_ABORT\n");
			
			break;
		case OBEX_EV_REQDONE:
			printf("OBEX_EV_REQDONE\n");
			if(mode == OBEX_MODE_CLIENT)
			{
				client_done(handle, obj, obex_cmd, obex_rsp);
			}
			else
			{
				server_done(handle, obj, obex_cmd, obex_rsp);
			}

			break;
		case OBEX_EV_REQHINT:
			printf("OBEX_EV_REQHINT\n");
			OBEX_ObjectSetRsp(obj, OBEX_RSP_CONTINUE, OBEX_RSP_SUCCESS);

			break;
		case OBEX_EV_REQ:
			printf("OBEX_EV_REQ\n");
			server_request(handle, obj, event, obex_cmd);
			break;
		case OBEX_EV_LINKERR:
			printf("OBEX_EV_LINKERR\n");
			OBEX_TransportDisconnect(handle);
			printf("Link broken!\n");
			break;
		case OBEX_EV_STREAMEMPTY:
			printf("OBEX_EV_STREAMEMPTY\n");
			fillstream(handle, obj);
			
			break;

		default:
			printf("OBEX_EV_ Unknown event %02x!\n", event);

			break;
	}
}

