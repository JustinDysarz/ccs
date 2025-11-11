#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <future>

#include "socket.h"
#include "crypto.h"

#define CONNECTIONS 100

void *handle(void *arg);

class server : public Socket {
private:
    std::unique_ptr<sockaddr_in> serverAddress;
    std::unique_ptr<pthread_attr_t> attr;

public:
    server(void);

    ~server(void);
};

#endif
