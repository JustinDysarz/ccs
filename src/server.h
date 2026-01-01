#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "crypto.h"

#define CONNECTIONS 100

void *handle(void *restrict arg);

static struct {
    struct sockaddr_in serverAddress;
    pthread_attr_t attr;
    int fd;
} server;

void server_listen(void);

#endif
