#include <iostream>
#include <exception>
#include <cassert>
#include <sstream>
#include "format.hpp"


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
    /*Complex(Complex &obj) : re_{obj.re_}, im_{obj.im_} {
        std::cout << "Complex (&)" << std::endl;
    }*/
    Complex(Complex &&obj) : re_{std::move(obj.re_)}, im_{std::move(obj.im_)} {
        std::cout << "Complex (&&)" << std::endl;
    }
    friend std::ostream &operator <<(std::ostream &out, Complex obj) {
        out << "(" << obj.re_ << ", " << obj.im_ << ")";
        return out;
    }
};


/* Test 1 */
/* Different valid uses */
void test_correct_use() 
{
    print_test_number();
    try {
        Complex a(1, 2), b(3, 4), c(4, 6), d(2, 4);
        double fp{5.42};
        std::string out;
        
        out = format("E: {0} + {1} = {2}, ok", a, b, c);
        assert(out == "E: (1, 2) + (3, 4) = (4, 6), ok" && "Invalid formating");     
        
        out = format("{0}+{0}={1}", a, "(2, 4)");
        assert(out == "(1, 2)+(1, 2)=(2, 4)" && "Invalid formating");
        
        out = format("{0}{1}{2}", "My num: ", a, ", end.");
        assert(out == "My num: (1, 2), end." && "Invalid formating");
        
        out = format("{0}{1}{2} and {4}", "My num: ", a, ", end.", b, fp, d);
        assert(out == "My num: (1, 2), end. and 5.42" && "Invalid formating");
        
        out = format("{0}{2}", "My num: ", a, ", end.", b, c, d);
        assert(out == "My num: , end." && "Invalid formating");
        
        out = format("no parenthesis", "My num: ", a, ", end.");
        assert(out == "no parenthesis" && "Invalid formating");
        
    } catch(const std::exception &exc) {
        std::cout << exc.what() << std::endl;
        assert("Error!");
    }
}

/* Test 2 */
/* Invalid indices in format string */
void test_format_index_error() 
{
    print_test_number();
    try {
        int a{1}, b{10};
        std::string out;
        out = format("{0} {1", a, b);
        assert(0 && "Undetected index error");
    } catch(const format_index_error &exc) {
        std::cout << "Correctly detected index error: " << exc.what();
        std::cout << std::endl;
    }
    
    try {
        int a{1}, b{10};
        std::string out;
        out = format("q {  1} ", a, b);
        assert(0 && "Undetected index error");
    } catch(const format_index_error &exc) {
        std::cout << "Correctly detected index error: " << exc.what();
        std::cout << std::endl;
    }
    
    try {
        int a{1}, b{10};
        std::string out;
        out = format("sd{0+}s", a, b);
        assert(0 && "Undetected index error");
    } catch(const format_index_error &exc) {
        std::cout << "Correctly detected index error: " << exc.what();
        std::cout << std::endl;
    }
    
    try {
        int a{1}, b{10};
        std::string out;
        out = format("{-1}", a, b);
        assert(0 && "Undetected index error");
    } catch(const format_index_error &exc) {
        std::cout << "Correctly detected index error: " << exc.what();
        std::cout << std::endl;
    }
    
    try {
        int a{1};
        std::string out;
        out = format("{}", a);
        assert(0 && "Undetected index error");
    } catch(const format_index_error &exc) {
        std::cout << "Correctly detected index error: " << exc.what();
        std::cout << std::endl;
    }
    
    try {
        int a{1};
        std::string out;
        out = format("{9999999999999999999999999999}", a);
        assert(0 && "Undetected index error");
    } catch(const format_index_error &exc) {
        std::cout << "Correctly detected index error: " << exc.what();
        std::cout << std::endl;
    }
    std::cout << "Report: OK" << std::endl;
}


/* Test 3 */
/* Invalid arguments for substitution */
void test_format_argument_error() 
{
    print_test_number();
    try {
        double a{1.2}, b{5.7}, c{6.12};
        std::string out;
        out = format("a = {0}, b = {3}", a, b, c);
        assert(0 && "Undetected argument error");
    } catch(const format_argument_error &exc) {
        std::cout << "Correctly detected argument error: " << exc.what();
        std::cout << std::endl;
    }
    
    try {
        double a{1.2}, c{6.12};
        std::string out;
        out = format("a = {0}, c = {2}", a, c);
        assert(0 && "Undetected argument error");
    } catch(const format_argument_error &exc) {
        std::cout << "Correctly detected argument error: " << exc.what();
        std::cout << std::endl;
    }
    
    try {
        double a{1.2};
        std::string out;
        out = format("a = {1}, b = {0} ", a);
        assert(0 && "Undetected argument error");
    } catch(const format_argument_error &exc) {
        std::cout << "Correctly detected argument error: " << exc.what();
        std::cout << std::endl;
    }
    
    
    std::cout << "Report: OK" << std::endl;
}

void test_long() 
{
    print_test_number();
    try {
        Complex a(1, 2), b(3, 4), c(4, 6);
        std::string out;
        out = format("{0}{1}{2} {1}{0} {0}{2}{1}", a, b, c);
        assert(out == "(1, 2)(3, 4)(4, 6) (3, 4)(1, 2) (1, 2)(4, 6)(3, 4)" &&
               "Invalid formating");
    } catch(const std::exception &exc) {
        std::cout << exc.what() << std::endl;
        assert("Error!");
    }
}




int main() 
{
    test_correct_use();
    test_format_index_error();
    test_format_argument_error();
    test_long();
    
    return 0;
}
