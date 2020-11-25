#include <iostream>
#include <exception>
#include <cassert>
#include "vector.hpp"


struct Complex {
    int re_, im_;
    int *ptr;
    Complex(int re = 0, int im = 0) : re_{re}, im_{im}, ptr{new int[10]} {
        //std::cout << "Complex (" << re_ >> "," << im_ << ") << std::endl;
    }
    Complex(const Complex &obj) : re_{obj.re_}, im_{obj.im_}, ptr{new int[10]} {
        //std::cout << "Complex (const &)" << std::endl;
    }
    Complex(Complex &&obj) : re_{std::move(obj.re_)}, im_{std::move(obj.im_)} {
        delete[] ptr;
        ptr = std::move(obj.ptr);
        obj.ptr = nullptr;
        //std::cout << "Complex (&&)" << std::endl;
    }
    
    Complex &operator =(const Complex &obj) {
        re_ = obj.re_;
        im_ = obj.im_;
        delete[] ptr;
        ptr = new int[10];
        //std::cout << "operator =(const &)" << std::endl;
        return *this;
    }
    Complex &operator =(Complex &&obj) {
        re_ = std::move(obj.re_);
        im_ = std::move(obj.im_);
        delete[] ptr;
        ptr = std::move(obj.ptr);
        obj.ptr = nullptr;
        //std::cout << "operator =(&&)" << std::endl;
        return *this;
    }
    
    bool operator ==(const Complex &other) const {
        return re_ == other.re_ && im_ == other.im_;
    }
    
    bool operator !=(const Complex &other) const {
        return re_ != other.re_ || im_ != other.im_;
    }

    friend std::ostream &operator <<(std::ostream &out, const Complex &obj) {
        out << "(" << obj.re_ << ", " << obj.im_ << ")";
        return out;
    }
    ~Complex() {
        //std::cout << "~Complex (" << re_ >> "," << im_ << ") << std::endl;
        delete[] ptr;
    }
};


void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": " << std::endl;
    ++n;
}


template<class T>
void vector_out(const Vector<T> &vec) {
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;    
}


void test_indexing() {
    print_test_number();
    try {
        Vector<Complex> v(2, Complex(2, 5));
        assert(v[0] == Complex(2, 5) && "Operator[] error");
        
        Vector<Complex> c(3);
        assert(c[0] == Complex() && c[1] == Complex() && c[2] == Complex()
               && "Operator[] error");
    } catch(const std::exception &ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        assert(0 && "Unexpected exception");
    }
    try {
        Vector<Complex> v(2, Complex(2, 5));
        Complex a = v[2];
        assert(0 && "Uncaught out_of_range");
    } catch(const std::exception &ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }
    try {
        Vector<Complex> v(2, Complex(2, 5));
        Complex a = v[-1];
        assert(0 && "Uncaught out_of_range");
    } catch(const std::exception &ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }
    std::cout << "Result: OK" << std::endl;
}

void test_stat() {
    print_test_number();
    try {
        Vector<Complex> v(3);
        assert(v.size() == 3 && v.capacity() >= 3 && !v.empty() 
               && "Wrong stats");
        Vector<Complex> c(0);
        assert(c.size() == 0 && v.capacity() >= 0 && c.empty() 
               && "Wrong stats");
    } catch(const std::exception &ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        assert(0 && "Unexpected exception");
    }
    std::cout << "Result: OK" << std::endl;
}


void test_push_pop_emplace_back() {
    print_test_number();
    try {
        Vector<Complex> v(0);
        v.push_back(Complex(1, 2));
        assert(v.size() == 1 && v[0] == Complex(1, 2) && "Error in push_back");
        for (int i = 0; i < 8; ++i) {
            v.push_back(Complex(i, i + 1));
        }
        assert(v.size() == 9 && v[8] == Complex(7, 8) && "Error in push_back");
        
        v.emplace_back(Complex(-1, -2));
        assert(v.size() == 10 && v[9] == Complex(-1, -2) 
               && "Error in emplace_back");
               
        size_t old_cap = v.capacity();
        v.pop_back();
        assert(v.size() == 9 && v[8] == Complex(7, 8) && v.capacity() == old_cap
               && "Error in pop_back");
    
    } catch(const std::exception &ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        assert(0 && "Unexpected exception");
    }
    try {
        Vector<Complex> v(1, Complex(2, 5));
        v.pop_back();
        assert(v.size() == 0 &&  "Error in pop_back");
        v.pop_back();
        assert(0 && "Uncaught out_of_range");
    } catch(const std::exception &ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }
    std::cout << "Result: OK" << std::endl;
}


void test_clear_resize_reserve() {
    print_test_number();
    try {
        Vector<Complex> v(2);
        v.clear();
        assert(v.size() == 0 && "Error in clear");
        
        Complex a(1, 2), b(0, 0), c(5, 6);
        v.push_back(a);
        v.resize(3);
        assert(v.size() == 3 && v[0] == a && v[1] == b && v[2] == b
               && "Error in resize(size_t)");
               
        v.resize(5, a);
        assert(v.size() == 5 && v[0] == a && v[1] == b && v[2] == b
               && v[3] == a && v[4] == a && "Error in resize(size_t, c T&)");
        
        v.resize(1, c);
        assert(v.size() == 1 && v[0] == a && "Error in resize(size_t, c T&)");
        
        v.push_back(a);
        size_t old_size = v.size(), old_cap = v.capacity();
        v.reserve(100);
        assert(v.size() == old_size && v.capacity() >= 100 
               && v.capacity() >= old_cap && "Error in reserve");
        
    } catch(const std::exception &ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        assert(0 && "Unexpected exception");
    }
    std::cout << "Result: OK" << std::endl;
}


void test_iterate() {
    print_test_number();
    try {
        Vector<Complex> v(3);
        Complex a(7, 7), b(3, 3);
        for (auto it = v.begin(); it != v.end(); ++it) {
            *it = Complex(7, 7);
        }
        assert(v.size() == 3 && v[0] == a && v[1] == a && v[2] == a
               && "Error in begin, end");
        
        for (auto it = v.rbegin(); it != v.rend(); it++) {
            *it = Complex(3, 3);
        }
        assert(v.size() == 3 && v[0] == b && v[1] == b && v[2] == b
               && "Error in rbegin, rend");
        
    } catch(const std::exception &ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        assert(0 && "Unexpected exception");
    }
    std::cout << "Result: OK" << std::endl;
}


int main() 
{
    test_indexing();
    test_stat();
    test_push_pop_emplace_back();
    test_clear_resize_reserve();
    test_iterate();

    return 0;
}
