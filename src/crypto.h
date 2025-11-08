#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <future>
#include <iostream>

#define KEY_SIZE 16
#define PATH "/dev/urandom"
#define PAYLOAD_PATH "test.sh"

typedef char byte;

byte *genkey(void);

class crypto {
private:
    byte *key;
    byte *payload;
public:
    crypto(void);
};
