#include "crypto.h"

byte *genkey(void) {
    int fd;
    byte *key = (byte *)malloc(KEY_SIZE);
    /*
    open(PATH, O_RDONLY);
    read(fd, key, KEY_SIZE);*/

    for (size_t i = 0; i < KEY_SIZE; i++)
        key[i] = rand();
    return key;
}

crypto::crypto(void) {
    std::future<byte *> fkey = std::async(std::launch::async, genkey);
    std::future<byte *> fpayload = std::async(std::launch::async, [this]() {
        struct stat file_stat;
        byte *buff;
        int fd;

        if ((fd = open(PAYLOAD_PATH, O_RDONLY)) == -1) {
            perror("Open failed");
            exit(EXIT_SUCCESS);
        }

        fstat(fd, &file_stat);
        this->payload_size = file_stat.st_size;
        buff = (byte *)malloc(sizeof(byte) * (file_stat.st_size + 1));

        read(fd, buff, file_stat.st_size);
        buff[file_stat.st_size] = '\0';
        return buff;
    });

    this->payload = fpayload.get();
    this->key = fkey.get();
#ifdef TESTING
    puts(this->payload);
    printf("\n");
    write(1, this->key, KEY_SIZE);
    printf("\n");
#endif
}


crypto::crypto(byte *key, size_t payload_size, byte *payload) {
    this->key = key;
    this->payload_size = payload_size;
    this->payload = payload;
}


size_t crypto::get_key_size(void) {return KEY_SIZE;}
size_t crypto::get_payload_size(void) {return this->payload_size;}
byte *crypto::get_key(void) {return this->key;}
byte *crypto::get_payload(void) {return this->payload;}

void crypto::crypt(void) {
    for (size_t i = 0; i < this->payload_size; i++)
        this->payload[i] ^= this->key[i % KEY_SIZE];;

}

void crypto::crypt_key(void) {
    for (size_t i = 0; i < KEY_SIZE; i++)
        this->key[i] ^= g_key[i];
}

void crypto::print_buff(void) {
    puts(this->payload);
}

void crypto::print_key(void) {
    write(1, this->key, KEY_SIZE);
    printf("\n");
}
