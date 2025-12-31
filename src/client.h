#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>

#include "socket.h"
#include "crypto.h"

#define FILE "test.sh"
#define MAX_FILE_NAME 64

static struct {
    struct sockaddr_in *serverAddress;
    int fd;
} client;



void fun(void);
void client_connect(void);



#endif

