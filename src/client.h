#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <cstdio>
#include <memory>
#include <cstring>

#include "socket.h"

class client : public Socket {
private:
    std::unique_ptr<sockaddr_in> serverAddress;

public:
    client(void);
    ~client(void);
};
#endif
