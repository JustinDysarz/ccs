#include "server.h"

server::server(void) : Socket() {
    int clientSocket;
    int *handleSocket;
    pthread_t pthread;


    std::cout << "starting daemon\n";

    attr = std::make_unique<pthread_attr_t>();
    serverAddress = std::make_unique<sockaddr_in>();

    serverAddress.get()->sin_family =AF_INET;
    serverAddress.get()->sin_port = htons(8080);
    serverAddress.get()->sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr*)serverAddress.get(), sizeof(*serverAddress.get())) == -1) {
        perror("Oh no. Error on bind.");
        exit(EXIT_FAILURE);
    }

    if (pthread_attr_init(attr.get()) != 0) {
        perror("could not set pthread attributes");
        exit(EXIT_FAILURE);
    }

    if(pthread_attr_setdetachstate(attr.get(), PTHREAD_CREATE_DETACHED) != 0) {
        perror("Could not set pthread attributes");
        exit(EXIT_FAILURE);
    }

    std::cout << "Socket bound to address";

    if (listen(sock, CONNECTIONS) == -1) {
        perror("Could not listen on socket");
        exit(EXIT_FAILURE);
    }

    std::cout << "connected";

    while (true) {
        if ((clientSocket = accept(sock, 0, 0)) == -1) {
            perror("Failed to handle connection");
            continue;
        }

        std::cout << "Connection established";

        if ((handleSocket = (int *)malloc(sizeof(int))) == NULL){
            perror("Failed to initilize socket data");
            continue;
        }

        *handleSocket = clientSocket;

        if (pthread_create(&pthread, attr.get(), handle, (void *)handleSocket) != 0) {
            perror("Failed to create pthread");
            continue;
        }
    }
}

void *handle(void *arg) {
                int clientSocket = *((int *)arg);
                crypto *crypt = new crypto();

                crypt->crypt();
                crypt->crypt_key();

                write(clientSocket, crypt->get_key(), crypt->get_key_size());

                char *buff = (char *)malloc(BUFF_SIZE);
                snprintf(buff, sizeof(size_t), "%lu", crypt->get_payload_size());
                write(clientSocket, buff, sizeof(size_t));
                free(buff);

                write(clientSocket, crypt->get_payload(), crypt->get_payload_size());

                delete crypt;

                return (void *)0;
}

server::~server(void) {
        pthread_attr_destroy(attr.get());
        close(sock);
}
