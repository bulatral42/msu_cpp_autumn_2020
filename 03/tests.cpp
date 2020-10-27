#include <iostream>
#include <exception>
#include <cassert>
#include "matrix.h"


void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": ";
    ++n;
}

/* Test  */
/*  */
void test_()
{
    print_test_number();
    try {
        
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
}

/* Test 1 */
/* Shape getters */
void test_shape() 
{
    print_test_number();
    try {
        Matrix a(3, 4, 5);
        assert(a.get_rows() == 3 && "Wrong rows number\n");
        assert(a.get_columns() == 4 && "Wrong columns number\n");
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 2 */
/* Element getter and setter -- operator[][] -- correct using */
void test_elem_correct() 
{
    print_test_number();
    try {
        Matrix a(3, 6, 4);
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 6; ++j) {
                assert(a[i][j] == 4 && "Wrong element returned\n");
            }
        }
        a[1][3] = -8;
        assert(a[1][3] = -8 && a[0][0] == 4 && a[2][5] == 4 && "Incorrect element set\n");
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 3 */
/* Element getter and setter -- operator[][] -- incorrect using */
void test_elem_incorrect() 
{
    print_test_number();
    try {
        Matrix a(3, 6, 4);
        a[3][3] = -8;
        assert("Undetected out of rows range\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try {
        Matrix a(3, 6, 4);
        a[1][6] = -8;
        assert("Undetected out of columns range\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    std::cout << "OK" << std::endl;
}

/* Test 4 */
/* Correct constructors using */
void test_constructors_correct() 
{
    print_test_number();
    try {
        Matrix a{}, b(10), c(2, 3), d(3, 4, 5);
        if (a.get_rows() != 1 || a.get_columns() != 1 || a[0][0] != 0) {
            assert("Default constructor error\n");
        }
        if (b.get_rows() != 1 || b.get_columns() != 1 || a[0][0] != 10) {
            assert("Conversion constructor error\n");
        }
        if (c.get_rows() != 2 || c.get_columns() != 3) {
            for (size_t i = 0; i < 2; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    if (c[i][j] != 0) {
                        assert("Two args constructor error\n");
                    }
                }
            }
        }
        if (c.get_rows() != 3 || c.get_columns() != 4) {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    if (c[i][j] != 5) {
                        assert("Three args constructor error\n");
                    }
                }
            }
        }
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 5 */
/* Incorrect constructors using */
void test_constructors_incorrect() 
{
    print_test_number();
    try {
        Matrix a(0, 2);
        assert("Invalid matrix constructed\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try {
        Matrix b(3, 0, 1);
        assert("Invalid matrix constructed\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try {
        Matrix c(-2, -2);
        assert("Invalid matrix constructed\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try {
        Matrix d(0, -1, 3);
        assert("Invalid matrix constructed\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    std::cout << "OK" << std::endl;
}

/* Test 6 */
/* Exual matrices -- operator == */
void test_equation()
{
    print_test_number();
    try {
        Matrix a(3, 4), b(3, 4), c(3, 4, 1);
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                a[i][j] = b[i][j] = -1;
            }
        }
        assert(a == b && "Equal matrices marked as unequal\n");
        assert(!(a == c) && "Unequal matrices marked as equal\n");
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    try {
        Matrix a(3, 4, 2), b(3, 5, 2);
        bool c = a == b;
        c = 1 && c;
        assert("Invalid matrix comparison\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
}




int main() 
{
    test_shape();
    test_elem_correct();
    test_elem_incorrect();
    test_constructors_correct();
    test_constructors_incorrect();
    test_equation();
    
    
    
    /*constexpr size_t n = 2, m = 2;
    Matrix a(m, n, 10), b(m, n, 5);
    Matrix c = a + b, d = a - b, e = a * b, f = a / b;
    int32_t q = 2;
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    
    c = a + q;
    d = a - q;
    e = a * q;
    f = a / q;
    
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    
    c = q + a;
    d = q - a;
    e = q * a;
    f = q / a;
    
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    
    std::cout << Matrix(10) + 1 << std::endl;
    */
    //a[0][n] = 0;
    //a[n][0] = 0;
       
    return 0;
}
