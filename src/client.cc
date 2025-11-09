#include <stdio.h>
#include <sys/socket.h>

#include "client.h"

client::client(void) : Socket() {
    struct addrinfo hint;
    struct addrinfo *tmp;
    struct sockaddr_in *result = new struct sockaddr_in;
    size_t payload_size;
    byte *payload_size_buff;
    byte *key;
    byte *payload;

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

    key = (byte *)malloc(sizeof(KEY_SIZE));
    payload_size_buff = (char *)malloc(sizeof(size_t));

    read(sock, key, KEY_SIZE);
    read(sock, payload_size_buff, sizeof(size_t));

    sscanf(payload_size_buff, "%lu", &payload_size);
    free(payload_size_buff);
    payload_size_buff = NULL;

    payload = (byte *)malloc(payload_size);
        
    read(sock, payload, payload_size);

    crypto *crypt = new crypto(key, payload_size, payload);
    crypt->crypt_key();
    crypt->crypt();


    delete crypt;
    crypt = nullptr;

    shutdown(sock, 0);
}

client::~client(void) {
    close(sock);
}
