#include "socket.h"

Socket::Socket(void) {
        this->sock = socket(AF_INET, SOCK_STREAM, 0);
}
