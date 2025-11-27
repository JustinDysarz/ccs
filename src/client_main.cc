#include "client.h"

#include <thread>

int main(void) {
    auto fn = []() {
        client start = client();
    };

    std::thread try1 = std::thread(fn);
    std::thread try2 = std::thread(fn);
    std::thread try3 = std::thread(fn);
    std::thread try4 = std::thread(fn);

    try1.join();
    try2.join();
    try3.join();
    try4.join();

    exit(EXIT_SUCCESS);
}
