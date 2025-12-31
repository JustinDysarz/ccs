#define TESTING

#include <stdlib.h>
#include "../src/crypto.h"
#include "../src/server.h"
#include "../src/client.h"

int main(void) {
    crypto_init_server();
    
    printf("\nPayload: \n");
    print_buff();
    printf("\n");

    printf("\nEncrypted payload: \n");
    crypt_buff();
    print_buff();
    printf("\n");


    printf("\nKey: \n");
    print_key();

    printf("\nEncrypted key: \n");
    crypt_key();
    print_key();


    printf("\nDecrypted key: \n");
    crypt_key();
    print_key();

    crypt_buff();


    printf("\nDecrypted payload: \n");
    print_buff();
    printf("\n");

    fun();

    free(crypto.payload);
    crypto.payload = NULL;

    free(crypto.key);
    crypto.key = NULL;
    crypto.payload = NULL;

    printf("Time to test the sockets\n\n\n");

/*    auto master = std::thread([]() {
        server_listen();
            });

    master.detach();

    sleep(5);

    auto client1 = std::thread([]() {
        client_connect(); 
            });



    client1.join();
*/
    exit(EXIT_SUCCESS);
}

