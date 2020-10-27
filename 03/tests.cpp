#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <cassert>
#include <sstream>
#include "matrix.h"

int main() 
{
    
    constexpr size_t n = 2, m = 2;
    Matrix a(m, n, 10), b(m, n, 5);
    Matrix c = a + b, d = a - b, e = a * b, f = a / b;
    int32_t q = 2;
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    /*std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    */
    c = a + q;
    d = q - b;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    /*c = a + q;
    std::cout << c << std::endl;
    d = a - q;
    e = a * q;
    f = a / q;
    
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    

    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    
    //a[0][n] = 0;
    //a[n][0] = 0;
    */   
    return 0;
}
