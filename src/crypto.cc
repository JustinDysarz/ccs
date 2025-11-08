#include "crypto.h"

byte *genkey(void) {
    int fd;
    byte *key = (byte *)malloc(KEY_SIZE);
    open(PATH, O_RDONLY);
    read(fd, key, KEY_SIZE);
    return key;
}

crypto::crypto(void) {
    std::future<byte *> fkey = std::async(std::launch::async, genkey);
    std::future<byte *> fpayload = std::async(std::launch::async, []() {
        struct stat file_stat;
        byte *buff;
        int fd;

        if ((fd = open(PAYLOAD_PATH, O_RDONLY)) == -1) {
            perror("Open failed");
            exit(EXIT_SUCCESS);
        }

        fstat(fd, &file_stat);
        buff = (byte *)malloc(sizeof(byte) * (file_stat.st_size + 1));

        read(fd, buff, file_stat.st_size);
        buff[file_stat.st_size] = '\0';
        return buff;
    });

    this->payload = fpayload.get();
    this->key = fkey.get();
    write(1, this->payload, KEY_SIZE);
    puts(this->key);
}
