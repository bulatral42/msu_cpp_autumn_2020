template<class Func, class... ArgsT>
auto ThreadPool::exec(Func func, ArgsT... args) -> 
        std::future<decltype(func(args...))> {
    using Promise = std::promise<decltype(func(args...))>;
    Promise *p_ptr = new std::promise<decltype(func(args...))>();
    auto fut_res = p_ptr->get_future();
    auto wrapper = 
            [this](Promise *p_ptr, Func func, ArgsT... args)
            {
                make_task(p_ptr, func, args...);
            };
    std::function<void()> new_task = std::bind(wrapper, p_ptr, func, args...);
    q_lock.lock();
    tasks.push(std::move(new_task));
    q_lock.unlock();
    alarm.notify_one();
    return fut_res;
}

template<class Func, class... ArgsT>
void ThreadPool::make_task(std::promise<void> *p_ptr, Func func, ArgsT... args) {
    func(args...);
    p_ptr->set_value();
    delete p_ptr;
}

template<class PromisePtr, class Func, class... ArgsT>
void ThreadPool::make_task(PromisePtr p_ptr, Func func, ArgsT... args) {
    p_ptr->set_value(func(args...));
    delete p_ptr;
}

