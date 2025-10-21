#include "socket.h"

Socket::Socket(void) {
    
        sock = socket(AF_INET, SOCK_STREAM, 0);
}
