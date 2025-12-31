#ifndef CRYPTO_H
#define CRYPTO_H

#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define KEY_SIZE 16
#define PATH "/dev/random"
#define PAYLOAD_PATH "test.sh"



static const char *g_key =  "aksht746351-*&$^";



static struct {
    size_t payload_size;
    uint8_t *key;
    uint8_t *payload;
} crypto;


void crypto_init_server(void);
void crypto_init_client(uint8_t *key, size_t payload_size, uint8_t *payload);

uint8_t *genkey(void);
size_t get_key_size(void);
size_t get_payload_size(void);
uint8_t *get_key(void);
uint8_t *get_payload(void);
void crypt_buff(void);
void crypt_key(void);
void print_buff(void);
void print_key(void);

#endif
