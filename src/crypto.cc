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
        /*TODO
         * Read payload file
         */
        byte *tmp = new byte[64];
        return tmp;
    });

    this->key = fkey.get();
    this->payload = fpayload.get();
    puts(this->key);
}
