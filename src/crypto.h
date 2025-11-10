#ifndef CRYPTO_H
#define CRYPTO_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <future>
#include <iostream>

#define KEY_SIZE 16
#define PATH "/dev/urandom"
#define PAYLOAD_PATH "test.sh"

typedef char byte;


static const char *g_key =  "aksht746351-*&$^";

byte *genkey(void);


class crypto {
private:
    byte *key;
    byte *payload;
    size_t payload_size;
public:
    crypto(void);
    crypto(byte *key, size_t payload_size, byte *payload);
    ~crypto(void);
    size_t get_key_size(void);
    size_t get_payload_size(void);
    byte *get_key(void);
    byte *get_payload(void);
    void crypt(void);
    void crypt_key(void);
    void print_buff(void);
    void print_key(void);
};

#endif
