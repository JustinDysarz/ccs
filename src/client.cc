#include <stdio.h>
#include <sys/socket.h>

#include "client.h"

client::client(void) : Socket() {
    struct addrinfo hint;
    struct addrinfo *tmp;
    struct sockaddr_in *result = new struct sockaddr_in;

    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(HOST, NULL, &hint, &tmp)) {
        perror("getaddinfo failed");
        exit(EXIT_FAILURE);
    }

    memcpy(&result, tmp->ai_addr, sizeof(struct sockaddr));

    freeaddrinfo(tmp);
    
    serverAddress = std::unique_ptr<sockaddr_in>(result);
    serverAddress.get()->sin_family = AF_INET;
    serverAddress.get()->sin_port = htons(8080);
    serverAddress.get()->sin_addr.s_addr = INADDR_LOOPBACK;

    if (connect(sock, (struct sockaddr*)(serverAddress.get()), sizeof(*serverAddress.get())) == -1) {
        perror("Oh no. could not connect to host");
        exit(EXIT_FAILURE);
    }
        
    const char *test = "Hello this is a test";
    send(sock, test, strlen(test), 0);
    shutdown(sock, 0);
}

client::~client(void) {
    close(sock);
}
