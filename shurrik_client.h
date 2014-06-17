#ifndef SHURRIK_CLIENT_H
#define SHURRIK_CLIENT_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_FIFO_NAME "/tmp/shurrik_serv_fifo"
#define CLIENT_FIFO_NAME "/tmp/shurrik_cli_%d_fifo"

#define BUFFER_SIZE 8192

typedef struct data_to_pass_st {
	pid_t client_pid;
	char  some_data[BUFFER_SIZE - 1];
} ShurrikData;

#endif
