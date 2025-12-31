#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <memory>
#include <future>

#include "socket.h"
#include "crypto.h"

#define CONNECTIONS 100

void *handle(void *arg);

typedef struct {
    sockaddr_in serverAddress;
    pthread_attr_t attr;
    int fd;
} server;

static server scon;

void server_listen(void);

#endif
