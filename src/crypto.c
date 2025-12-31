#include "crypto.h"

uint8_t *genkey(void) {
    uint8_t *key;
    int fd;

    key = (uint8_t *)malloc(KEY_SIZE);

    fd = open(PATH, O_RDONLY);
    read(fd, key, KEY_SIZE);
    return key;
}


uint8_t *payload_init() {
        struct stat file_stat;
        uint8_t *buff;
        int fd;

        if ((fd = open(PAYLOAD_PATH, O_RDONLY)) == -1) {
            perror("Open failed");
            exit(EXIT_SUCCESS);
        }

        fstat(fd, &file_stat);
        crypto.payload_size = file_stat.st_size;
        buff = (uint8_t *)malloc(sizeof(uint8_t) * (file_stat.st_size + 1));

        read(fd, buff, file_stat.st_size);
        buff[file_stat.st_size] = '\0';
        close(fd);
        return buff;
    }

void crypto_init_server(void) {
    crypto.key = genkey();
    crypto.payload = payload_init();
}

void crypto_init_client(uint8_t *key, size_t payload_size, uint8_t *payload) {
    crypto.key = key;
    crypto.payload_size = payload_size;
    crypto.payload = payload;
}

size_t get_key_size(void) {return KEY_SIZE;}
size_t get_payload_size(void) {return crypto.payload_size;}
uint8_t *get_key(void) {return crypto.key;}
uint8_t *get_payload(void) {return crypto.payload;}

void crypt_buff(void) {
    for (size_t i = 0; i < crypto.payload_size; i++)
        crypto.payload[i] ^= crypto.key[i % KEY_SIZE];
}

void crypt_key(void) {
    for (size_t i = 0; i < KEY_SIZE; i++)
        crypto.key[i] ^= g_key[i];
}

void print_buff(void) {
    printf("%s\n", crypto.payload);
}

void print_key(void) {
    write(1, crypto.key, KEY_SIZE);
    printf("\n");
}
