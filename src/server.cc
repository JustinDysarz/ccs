#include "server.h"

void server_listen(void) {
    int clientSocket;
    int *handleSocket;
    pthread_t pthread;

    scon.fd= socket(AF_INET, SOCK_STREAM, 0);
    memset(&scon.serverAddress, 0, sizeof scon.serverAddress);

    scon.serverAddress.sin_family =AF_INET;
    scon.serverAddress.sin_port = htons(8080);
    scon.serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(scon.fd, (struct sockaddr*)&scon.serverAddress, sizeof(scon.serverAddress)) == -1) {
        perror("Oh no. Error on bind.");
        exit(EXIT_FAILURE);
    }

    if (pthread_attr_init(&scon.attr) != 0) {
        perror("could not set pthread attributes");
        exit(EXIT_FAILURE);
    }

    if(pthread_attr_setdetachstate(&scon.attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("Could not set pthread attributes");
        exit(EXIT_FAILURE);
    }

    std::cout << "Socket bound to address";

    if (listen(scon.fd, CONNECTIONS) == -1) {
        perror("Could not listen on socket");
        exit(EXIT_FAILURE);
    }

    std::cout << "\nconnected\n";

    while (true) {
        if ((clientSocket = accept(scon.fd, 0, 0)) == -1) {
            perror("Failed to handle connection");
            continue;
        }

        std::cout << "\nConnection established\n";

        if ((handleSocket = (int *)malloc(sizeof(int))) == NULL){
            perror("Failed to initilize socket data");
            continue;
        }

        *handleSocket = clientSocket;

        if (pthread_create(&pthread, &scon.attr, handle, (void *)handleSocket) != 0) {
            perror("Failed to create pthread");
            continue;
        }
    }
    shutdown(scon.fd, SHUT_RDWR);
    pthread_attr_destroy(&scon.attr);
    close(scon.fd);
}

void *handle(void *arg) {
                int clientSocket = *((int *)arg);
                crypto *crypt = new crypto();

                crypt->crypt();
                crypt->crypt_key();

                write(clientSocket, crypt->get_key(), crypt->get_key_size());

                char *buff = (char *)malloc(BUFF_SIZE);
                memset(buff, 0, BUFF_SIZE);
                snprintf(buff, sizeof(size_t), "%lu", crypt->get_payload_size());
                write(clientSocket, buff, sizeof(BUFF_SIZE));

                free(buff);
                buff = (char *)0;

                write(clientSocket, crypt->get_payload(), crypt->get_payload_size());
                shutdown(clientSocket, SHUT_RDWR);

                free(arg);
                arg = (void *)0;
                delete crypt;

                close(clientSocket);

                return (void *)0;
}
