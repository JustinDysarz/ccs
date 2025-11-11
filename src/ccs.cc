#include "socket.h"
#include "server.h"


#ifndef TESTING
int main(void) {
    pid_t pid;

    std::cout << "Starting daemon\n";
    
    umask(0);

    if ((pid = fork()) < 0) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }

    if (pid != 0) {
        puts("Daemon initialized\n");
        exit(EXIT_SUCCESS);
    }

    setsid();


    server master = server();


    exit(EXIT_SUCCESS);
}
#endif
