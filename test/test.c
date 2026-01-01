#define TESTING

#include <stdlib.h>
#include <threads.h>
#include <assert.h>
#include "../src/crypto.h"
#include "../src/server.h"
#include "../src/client.h"

static uint8_t key_copy[KEY_SIZE], *buff_copy;
static thrd_t master, client1;


int main(void) {
    crypto_init_server();

    strncpy((char *)key_copy, (char *)get_key(), KEY_SIZE);
    crypt_key();
    crypt_key();
    assert(strcmp((char *)get_key(), (char *)key_copy) == 0);

    buff_copy = (uint8_t *)malloc(get_payload_size());
    strncpy((char *)buff_copy, (char *)get_payload(), get_payload_size());
    assert(strcmp((char *)get_payload(), (char *)buff_copy) == 0);
    puts("All asserts passed");

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

    thrd_create(&master, (void *)server_listen, NULL);
    thrd_create(&client1, (void *)client_connect, NULL);

    thrd_join(master, NULL);
    thrd_join(client1, NULL);

    exit(EXIT_SUCCESS);
}

