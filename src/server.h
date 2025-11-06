#ifndef SERVER_H
#define SERVER_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <future>

#include "socket.h"

#define CONNECTIONS 100

class server : public Socket {
private:
    std::unique_ptr<sockaddr_in> serverAddress;

public:
    server(void);

    ~server(void);
};

#endif
