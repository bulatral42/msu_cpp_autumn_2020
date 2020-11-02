#include <iostream>
#include <exception>
#include <cassert>
#include <sstream>
#include "big_int.h"

void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": ";
    ++n;
}

int main() 
{
    /*BigInt a{23456}, b{"   \t  \n -0001234567890123456789012"};
    std::cout << (a < b) << std::endl;
    std::cout << (a > b) << std::endl;
    std::cout << (a <= b) << std::endl;
    std::cout << (a >= b) << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << (a != b) << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    BigInt c(a);
    std::cout << a << std::endl;
    std::cout << b << std::endl;*/
    BigInt a{100}, b{10};
    const BigInt c{-100};
    BigInt d = -10;
    /*std::cout << a + b << std::endl;
    std::cout << b + a << std::endl;
    std::cout << a - b << std::endl;
    std::cout << b - a << std::endl;*/
    std::cout << a + c << std::endl;
    std::cout << c + a << std::endl;
    std::cout << a - a << std::endl;
    std::cout << c - c << std::endl;

    /*a = b;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    a = c;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    a = b = c;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    
    a = std::move(d);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;*/
    return 0;
}
