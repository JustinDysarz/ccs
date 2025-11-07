#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <cstdio>
#include <memory>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>

#include "socket.h"

#define HOST "enter.host.com"

class client : public Socket {
private:
    std::unique_ptr<sockaddr_in> serverAddress;

public:
    client(void);
    ~client(void);
};
#endif
