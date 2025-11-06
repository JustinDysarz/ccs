#include "server.h"

server::server(void) : Socket() {
    serverAddress = std::make_unique<sockaddr_in>();
    serverAddress.get()->sin_family =AF_INET;
    std::cout << "start\n";
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
            char *buff = (new char[1024]);
            recv(clientSocket, buff, sizeof(buff), 0);
            std::string str = std::string(buff);
            std::cout << "test output from connection: " << str << "\n";});

            std::thread([clientSocket]() {
                char *buff = (new char[1024]);
                recv(clientSocket, buff, sizeof(buff), 0);
                std::string str = std::string(buff);
                std::cout << "test output from connection: " << str << "\n";}).detach();
    }
}

server::~server(void) {
        close(sock);
}
