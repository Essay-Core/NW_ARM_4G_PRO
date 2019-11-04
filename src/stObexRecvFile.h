#ifndef __STOBEXRECVFILE_H
#define __STOBEXRECVFILE_H

#include "openobex/obex.h"
#include "obex_test.h"
#include "obex_test_client.h"
#include "obex_test_server.h"

#include <sys/time.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>

void cb_obex_init(obex_t *handle, obex_object_t *obj,int mode, int enent, int obex_cmd, int obex_rsp);
//int read_input(char* answer, size_t size, const char*question, ...);
//int recv_file();

#endif