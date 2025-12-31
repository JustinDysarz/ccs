#ifndef SOCKET_H
#define SOCKET_H

#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFF_SIZE 32

class Socket {
public:
    int sock;

    Socket(void);
};

#endif
