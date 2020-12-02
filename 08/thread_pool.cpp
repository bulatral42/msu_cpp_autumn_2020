#include <thread>
#include <vector>
#include <future>
#include <functional>

#include "thread_pool.hpp"


ThreadPool::ThreadPool(size_t pool_size) : still_working{true} {
    for (size_t i = 0; i < pool_size; ++i) {
        workers.emplace_back(
                [this]() {
                    while (still_working) {
                        std::unique_lock<std::mutex> lock(q_lock);
                        if (tasks.empty()) {
                            alarm.wait(lock, 
                                    [this]() {
                                        return this->tasks.empty(); 
                                    });
                        } else {
                            auto new_task = std::move(tasks.front());
                            tasks.pop();
                            lock.unlock();
                            new_task();
                        }
                    }
                });
    }
}

ThreadPool::~ThreadPool() {
    if (still_working) {
        still_working = false;
        alarm.notify_all();
        for (auto& worker : workers) {
            worker.join();
        }
    }
}
    


