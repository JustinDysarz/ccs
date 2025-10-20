#include "lib.h"
#include <thread>

/*
 * TODO
 * Create function for threads to handle connections
 */
worker::worker(u64 id) {
        this->id = id;
        thread = std::thread();
}

/*
 * TODO
 * Set up ipc for pool to send a connection handler
 * for workers.
 */
thread_pool::thread_pool() {
        pool = std::vector<worker>(WORKERS);
    }
