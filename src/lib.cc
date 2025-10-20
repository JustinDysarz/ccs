#include "lib.h"

#include <functional>
#include <memory>
#include <thread>

/*
 * TODO: add error handling
 */

task_manager::task_manager(void) : tasks(){}

task_manager::~task_manager(void) {
        while (!this->tasks.empty())
            this->tasks.pop();
}

void task_manager::insert(std::function<void()> fn) {
    this->tasks.push(fn);
}

auto task_manager::get(void) {
    std::function<void()> ret = this->tasks.front();
    this->tasks.pop();

    return ret;
}

worker::worker(u64 id, std::shared_ptr<task_manager> client) 
    :id(id),
    client(client),
    /*Handle incoming connections*/
    thread([this]() {
                while (true) {
                    auto fn = this->client.lock()->get();
                    fn();}}){
        isWorking = false;
    }

/*FIXME
 * fix destructor
 */
//worker::~worker(void) = default;

thread_pool::thread_pool(void) : pool(), manager() {
        for (u64 i = 0; i < WORKERS; i++) 
            this->pool.emplace_back(worker(i, manager));
}

void thread_pool::handle(std::function<void()> fn) {
    this->manager->insert(fn);
}
