#include "server.h"

server::server(void) : Socket() {
    serverAddress = std::make_unique<sockaddr_in>();
    serverAddress.get()->sin_family =AF_INET;
    std::cout << "starting daemon\n";
    serverAddress.get()->sin_port = htons(8080);
    serverAddress.get()->sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr*)serverAddress.get(), sizeof(*serverAddress.get())) == -1) {
        perror("Oh no. Error on bind.");
        exit(EXIT_FAILURE);
    }

    listen(sock, CONNECTIONS);
    std::cout << "connected";

    while (true) {
        int clientSocket = accept(sock, nullptr, nullptr);

            std::thread([clientSocket]() {
                crypto *crypt = new crypto();
                crypt->crypt();
                crypt->crypt_key();

                char *buff = (char *)malloc(sizeof(size_t));
                snprintf(buff, sizeof(size_t), "%lu", crypt->get_payload_size());
                write(clientSocket, crypt->get_key(), crypt->get_key_size());
                write(clientSocket, buff, sizeof(size_t));
                free(buff);
                write(clientSocket, crypt->get_payload(), crypt->get_payload_size());
                delete crypt;
            });
    };
}

server::~server(void) {
        close(sock);
}
