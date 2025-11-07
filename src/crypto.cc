#include "crypto.h"

byte *genkey(void) {
    int fd;
    byte *key = new byte[KEY_SIZE];
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
        buff = (byte *)malloc(sizeof(byte) * file_stat.st_size);

        read(fd, buff, file_stat.st_size);
        return buff;
    });

    this->key = fkey.get();
    this->payload = fpayload.get();
    puts(this->key);
}
