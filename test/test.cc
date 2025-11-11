#define TESTING

#include <cstdlib>
#include "../src/crypto.h"
#include "../src/server.h"
#include "../src/client.h"

int main(void) {
    crypto *crypt = new crypto();
    
    printf("\nPayload: \n");
    crypt->print_buff();
    printf("\n");

    printf("\nEncrypted payload: \n");
    crypt->crypt();
    crypt->print_buff();
    printf("\n");


    printf("\nKey: \n");
    crypt->print_key();

    printf("\nEncrypted key: \n");
    crypt->crypt_key();
    crypt->print_key();


    printf("\nDecrypted key: \n");
    crypt->crypt_key();
    crypt->print_key();

    crypt->crypt();


    printf("\nDecrypted payload: \n");
    crypt->print_buff();
    printf("\n");

    fun(crypt);

    delete crypt;
    crypt = nullptr;

    std::cout << "Time to test the sockets\n\n\n";

    auto master = std::thread([]() {
        server *serv = new server();
            });

    master.detach();

    auto client1 = std::thread([]() {
        client *client1 = new client();
            });


    auto client2 = std::thread([]() {
        client *client2 = new client();
            });

    auto client3 = std::thread([]() {
        client *client3 = new client();
            });


    auto client4 = std::thread([]() {
        client *client4 = new client();
            });

    client1.join();
    client2.join();
    client3.join();
    client4.join();

    exit(EXIT_SUCCESS);
}

