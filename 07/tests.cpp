#include <iostream>
#include <exception>
#include <cassert>
#include "vector.hpp"
//#include "allocator.hpp"

static int cnt = 0, dnt = 0;


void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": " << std::endl;
    ++n;
}


struct Complex {
    int re_, im_;
    int *ptr;
    Complex(int re = 0, int im = 0) : re_{re}, im_{im}, ptr{new int[10]} {
        ++cnt;
        std::cout << "Complex (): " << re_ << "  " << im_ << std::endl;
    }
    Complex(const Complex &obj) : re_{obj.re_}, im_{obj.im_}, ptr{new int[10]} {
        ++cnt;
        std::cout << "Complex (const &)" << std::endl;
    }
    Complex(Complex &&obj) : re_{std::move(obj.re_)}, im_{std::move(obj.im_)} {
        delete[] ptr;
        ptr = std::move(obj.ptr);
        obj.ptr = nullptr;
        std::cout << "Complex (&&)" << std::endl;
    }
    
    Complex &operator =(const Complex &obj) {
        re_ = obj.re_;
        im_ = obj.im_;
        
        if (ptr == nullptr) {
            std::cout << "deleting nullptr..." << std::endl;
        }
        delete[] ptr;
        ptr = new int[10];
        std::cout << "operator =(const &)" << std::endl;
        return *this;
    }
    Complex &operator =(Complex &&obj) {
        re_ = std::move(obj.re_);
        im_ = std::move(obj.im_);
        delete[] ptr;
        ptr = std::move(obj.ptr);
        obj.ptr = nullptr;
        std::cout << "operator =(&&)" << std::endl;
        return *this;
    }

    friend std::ostream &operator <<(std::ostream &out, const Complex &obj) {
        out << "(" << obj.re_ << ", " << obj.im_ << ")";
        return out;
    }
    ~Complex() {
        std::cout << "~Complex(): " << re_ << "  " << im_ << std::endl;
        ++dnt;
        if (ptr == nullptr) {
            std::cout << "deleting nullptr..." << std::endl;
        }
        delete[] ptr;
    }
};

template<class T>
void vec_out(const Vector<T> &vec) {
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "q: " << vec[i] << "p ";
    }
    std::cout << std::endl;    
}

int main() 
{
    int n = 1;
    Vector<Complex> v(n);
    
    std::cout << 'q' << std::endl;
    
    for (int i = 0; i < n; ++i) {
        v[i] = Complex(i, 1 + i);
    }
    vec_out(v);
    v.push_back(Complex(100, 200));
    vec_out(v);
    v.emplace_back(Complex(300, 400));
    vec_out(v);
    vec_out(v);
    vec_out(v);
    v.push_back(Complex(500, 600));
    vec_out(v);
    v.push_back(Complex(100, 200));
    vec_out(v);
    
    v.push_back(Complex(100, 200));
    vec_out(v);
    v.pop_back();
    vec_out(v);
    v.resize(2);
    vec_out(v);
    
    std::cout << "CNT: " << cnt << std::endl;
    std::cout << "DNT: " << dnt << std::endl;
    return 0;
}
