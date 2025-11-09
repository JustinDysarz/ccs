#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <cstdio>
#include <memory>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

#include "socket.h"
#include "crypto.h"

#define HOST "enter.host.com"
#define FILE "file\0"
#define MAX_FILE_NAME 64

void fun(crypto *crypt);

class client : public Socket {
private:
    std::unique_ptr<sockaddr_in> serverAddress;

public:
    client(void);
    ~client(void);
};

#endif

