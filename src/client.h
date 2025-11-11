#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <cstdio>
#include <memory>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>

#include "socket.h"
#include "crypto.h"

#define FILE "file\0"
#define MAX_FILE_NAME 64

static const char *host = "localhost";

void fun(crypto *crypt);

class client : public Socket {
private:
    struct sockaddr_in *serverAddress;

public:
    client(void);
    ~client(void);
};

#endif

