#include <iostream>
#include <exception>
#include <cassert>
#include "vector.hpp"
//#include "allocator.hpp"


void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": " << std::endl;
    ++n;
}


struct Complex {
    int re_, im_;
    
    Complex(int re = 0, int im = 0) : re_{re}, im_{im} {}
    Complex(const Complex &obj) : re_{obj.re_}, im_{obj.im_} {
        std::cout << "Complex (const &)" << std::endl;
    }
    Complex(Complex &&obj) : re_{std::move(obj.re_)}, im_{std::move(obj.im_)} {
        std::cout << "Complex (&&)" << std::endl;
    }
    friend std::ostream &operator <<(std::ostream &out, const Complex &obj) {
        out << "(" << obj.re_ << ", " << obj.im_ << ")";
        return out;
    }
};


int main() 
{
    int n = 5;
    Vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = i;
    }
    
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
