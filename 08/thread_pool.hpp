#pragma once

#include <thread>
#include <vector>
#include <future>
#include <functional>
#include <queue>
#include<iostream>

const size_t DEFAULT_POOL_SIZE = std::thread::hardware_concurrency();


class ThreadPool
{
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    
    std::mutex q_lock;
    std::condition_variable alarm;
    std::atomic<bool> still_working;
    
public:
    explicit ThreadPool(size_t pool_size = DEFAULT_POOL_SIZE);
    ~ThreadPool();
    
    template<class Func, class... ArgsT>
    auto exec(Func func, ArgsT... args) -> std::future<decltype(func(args...))>;

private:
    template<class PromisePtr, class Func, class... ArgsT>
    void make_task(PromisePtr, Func, ArgsT...);
    template<class Func, class... ArgsT>
    void make_task(std::promise<void> *, Func, ArgsT...);
};

#include "thread_pool.tpp"

