#include "server.h"

void server_listen(void) {
    int clientSocket;
    int *handleSocket;
    pthread_t pthread;

    server.fd= socket(AF_INET, SOCK_STREAM, 0);
    memset(&server.serverAddress, 0, sizeof server.serverAddress);

    server.serverAddress.sin_family =AF_INET;
    server.serverAddress.sin_port = htons(8080);
    server.serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(server.fd, (struct sockaddr*)&server.serverAddress, sizeof(server.serverAddress)) == -1) {
        perror("Oh no. Error on bind.");
        exit(EXIT_FAILURE);
    }

    if (pthread_attr_init(&server.attr) != 0) {
        perror("could not set pthread attributes");
        exit(EXIT_FAILURE);
    }

    if(pthread_attr_setdetachstate(&server.attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("Could not set pthread attributes");
        exit(EXIT_FAILURE);
    }

    printf("Socket bound to address");

    if (listen(server.fd, CONNECTIONS) == -1) {
        perror("Could not listen on socket");
        exit(EXIT_FAILURE);
    }

    printf("\nconnected\n");

    while (1) {
        if ((clientSocket = accept(server.fd, 0, 0)) == -1) {
            perror("Failed to handle connection");
            continue;
        }

        printf("\nConnection established\n");

        if ((handleSocket = (int *)malloc(sizeof(int))) == NULL){
            perror("Failed to initilize socket data");
            continue;
        }

        *handleSocket = clientSocket;

        if (pthread_create(&pthread, &server.attr, handle, (void *)handleSocket) != 0) {
            perror("Failed to create pthread");
            continue;
        }
    }
    shutdown(server.fd, SHUT_RDWR);
    pthread_attr_destroy(&server.attr);
    close(server.fd);
}

void *handle(void *arg) {
                int clientSocket = *((int *)arg);

                crypto_init_server();
                crypt_buff();
                crypt_key();

                write(clientSocket, get_key(), get_key_size());

                char *buff = (char *)malloc(BUFF_SIZE);
                memset(buff, 0, BUFF_SIZE);
                snprintf(buff, sizeof(size_t), "%lu", get_payload_size());
                write(clientSocket, buff, sizeof(BUFF_SIZE));

                free(buff);
                buff = (char *)0;

                write(clientSocket, get_payload(), get_payload_size());
                shutdown(clientSocket, SHUT_RDWR);

                free(arg);
                arg = (void *)0;

                free(crypto.payload);
                crypto.payload = NULL;

                free(crypto.key);
                crypto.key = NULL;
                crypto.payload = NULL;

                close(clientSocket);

                return (void *)0;
}
