#ifndef SOCKET_H
#define SOCKET_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Socket {
public:
    int sock;

    Socket(void);
};

#endif
