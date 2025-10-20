#ifndef LIB_H
#define LIB_H

#include <thread>
#include <vector>

#define WORKERS 8

typedef unsigned long long u64;

class worker {
private:
u64 id;
std::thread thread;

public:
    worker(u64 id = 0);
    
};


class thread_pool {
private:
    std::vector<worker> pool;

public:
    thread_pool();
};

#endif
