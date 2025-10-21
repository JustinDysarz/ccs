#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <future>

#include "lib.h"

class server {
private:
    std::unique_ptr<sockaddr_in> serverAddress;
    std::unique_ptr<thread_pool> pool;
    int serverSocket;

public:
    server(void) {
        /*std::future<std::unique_ptr<thread_pool>> to_pool = std::async(std::launch::async, []() {
            return std::make_unique<thread_pool>();});*/
        
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);


        serverAddress = std::make_unique<sockaddr_in>();
        serverAddress.get()->sin_family =AF_INET;
        std::cout << "start\n";
        serverAddress.get()->sin_port = htons(8080);
        serverAddress.get()->sin_addr.s_addr = INADDR_ANY;
        if (bind(serverSocket, (struct sockaddr*)serverAddress.get(), sizeof(*serverAddress.get())) == -1) {
            perror("Oh no. Error on bind.");
            exit(EXIT_FAILURE);
        }

        listen(serverSocket, WORKERS);
        std::cout << "connected";

//        pool = to_pool.get();
        while (true) {
            int clientSocket = accept(serverSocket, nullptr, nullptr);

            /*pool->handle([clientSocket]() {
                char *buff = (new char[1024]);
                recv(clientSocket, buff, sizeof(buff), 0);
                std::string str = std::string(buff);
                std::cout << "test output from connection: " << str << "\n";});*/

            std::thread([clientSocket]() {
                char *buff = (new char[1024]);
                recv(clientSocket, buff, sizeof(buff), 0);
                std::string str = std::string(buff);
                std::cout << "test output from connection: " << str << "\n";});
        }
    }

    ~server(void) {
        close(serverSocket);
    }
};

int main(void) {
    server master = server();


    exit(EXIT_SUCCESS);
}
