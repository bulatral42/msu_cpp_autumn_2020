#include <iostream>
#include <exception>
#include <cassert>
#include <vector>

#include "thread_pool.hpp"


void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": " << std::endl;
    ++n;
}


void test_compare() {
    print_test_number();
    try {
        Vector<Complex> v(2, Complex(2, 5)), w(2, Complex(2, 5));
        assert(w == v && !(v != w) && "Comparison error");
    } catch(const std::exception &ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        assert(0 && "Unexpected exception");
    }
    std::cout << "Result: OK" << std::endl;
}
*/



int main() 
{
    ThreadPool pool(2);
    std::vector<std::future<int>> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(pool.exec([](int k) -> int { return k + 1; }, i));
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << v[i].get() << std::endl;
    }

    return 0;
}
