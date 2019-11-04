#ifndef __STRFCOMM_H
#define __STRFCOMM_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include <termios.h>
#include <sys/poll.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

//#include "kword.h"

#ifdef NEED_PPOLL
#include "ppoll.h"
#endif

static char *rfcomm_config_file = NULL;
static int rfcomm_raw_tty = 0;
static int auth = 0;
static int encryption = 0;
static int secure = 0;
static int master = 0;
static int linger = 0;

static char *rfcomm_state[] = {
	"unknown",
	"connected",
	"clean",
	"bound",
	"listening",
	"connecting",
	"connecting",
	"config",
	"disconnecting",
	"closed"
};

static volatile sig_atomic_t __io_canceled = 0;

void cmd_listen(int ctl, int dev, bdaddr_t *bdaddr, int argc, char **argv);

#endif
