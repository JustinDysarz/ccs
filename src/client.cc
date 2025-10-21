#include <cstdlib>
#include <cstdio>
#include <memory>
#include <cstring>

#include "socket.h"

class client : public Socket {
private:
    std::unique_ptr<sockaddr_in> serverAddress;

public:
    client(void) : Socket() {
        serverAddress = std::unique_ptr<sockaddr_in>();
        serverAddress.get()->sin_family = AF_INET;
        serverAddress.get()->sin_port = htons(8080);
        serverAddress.get()->sin_addr.s_addr = INADDR_LOOPBACK;

        if (connect(sock, (struct sockaddr*)&*(serverAddress.get()), sizeof(*serverAddress.get())) == -1) {
            perror("Oh no. could not connect to host");
            exit(EXIT_FAILURE);
        }
        
        const char *test = "Hello this is a test";
        send(sock, test, strlen(test), 0);
    }

    ~client(void) {
        close(sock);
    }
};

int main(void) {
    client start = client();

    exit(EXIT_SUCCESS);
}
