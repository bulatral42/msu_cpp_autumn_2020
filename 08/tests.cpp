#include <iostream>
#include <exception>
#include <cassert>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include<set>

#include "thread_pool.hpp"


void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": " << std::endl;
    ++n;
}


int sum(int a, int b) {
    return a + b;
}

void out(int a) {
    std::this_thread::sleep_for(std::chrono::microseconds(2));
    std::cout << "Out: " <<  a << std::endl;
}


void test_simple() {
    print_test_number();
    try {
        ThreadPool pool(2);
        std::vector<std::future<int>> v;
        for (int i = 0; i < 7; ++i) {
            v.push_back(pool.exec([](int k) -> int { return k + 1; }, i));
        }
        std::set<int> result, correct = { 1, 2, 3, 4, 5, 6, 7 };
        for (int i = 0; i < 7; ++i) {
            result.insert(v[i].get());
        }
        assert(result == correct && "Wrong result");
    } catch(const std::exception &ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        assert(0 && "Unexpected exception");
    }
    std::cout << "Result: OK" << std::endl;
}

void test_different_funcs() {
    print_test_number();
    try {
        ThreadPool pool(4);
        std::vector<std::future<int>> v1, v2;
        std::vector<std::future<void>> v3;
        for (int i = 0; i < 7; ++i) {
            v1.push_back(pool.exec([](int k) -> int { return k + 1; }, i));
        }
        for (int i = 0; i < 5; ++i) {
            v2.push_back(pool.exec(sum, i, -i));
        }
        for (int i = 0; i < 3; ++i) {
            v3.push_back(pool.exec(out, 2 * i));
        }
        std::set<int> result1, correct1 = { 1, 2, 3, 4, 5, 6, 7 };
        for (int i = 0; i < 7; ++i) {
            result1.insert(v1[i].get());
        }
        std::set<int> result2, correct2 = { 0, 0, 0, 0, 0 };
        for (int i = 0; i < 5; ++i) {
            result2.insert(v2[i].get());
        }
        for (int i = 0; i < 3; ++i) {
            v3[i].wait();
        }
        assert(result1 == correct1 && "Wrong result");
        assert(result2 == correct2 && "Wrong result");
    } catch(const std::exception &ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        assert(0 && "Unexpected exception");
    }
    std::cout << "Result: OK" << std::endl;
}



int main() 
{
    test_simple();
    test_different_funcs();

    return 0;
}
