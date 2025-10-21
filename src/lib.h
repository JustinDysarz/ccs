#ifndef LIB_H
#define LIB_H

#include <memory>
#include <queue>
#include <thread>
#include <functional>
#include <vector>
#include <iostream>

#define WORKERS 2

typedef unsigned long long u64;

/*
 * TODO: add error handling
 */

class task_manager {
private:
    std::queue<std::function<void()>> tasks;

public:
    task_manager(void);
    ~task_manager(void);

    void insert(std::function<void()> fn);
    auto get(void);
};

class worker {
private:
    std::thread thread;
    std::weak_ptr<task_manager> client;
    u64 id;

public:
    worker(u64 id, std::shared_ptr<task_manager> client);
    /*FIXME: destructor*/
   // ~worker(void);
};

 
class thread_pool {
private:
    std::vector<worker> pool;
    std::shared_ptr<task_manager> manager;

public:
    thread_pool(void);
    void handle(std::function<void()> task);
};

#endif
