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

    delete crypt;

    exit(EXIT_SUCCESS);
}
