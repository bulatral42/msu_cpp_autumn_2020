#include <iostream>
#include <exception>
#include <cassert>
#include <sstream>
#include "matrix.h"


void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": ";
    ++n;
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
        const Matrix b(2, 2, 1);
        assert(b[1][1] == 1 && "Wrong element returned\n");
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
/* Correct constructors using and operator = */
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
            assert("Two args constructor error\n");
        }
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                if (c[i][j] != 0) {
                    assert("Two args constructor error\n");
                }
            }
        }
        if (d.get_rows() != 3 || d.get_columns() != 4) {
            assert("Three args constructor error\n");
        }
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                if (d[i][j] != 5) {
                    assert("Three args constructor error\n");
                }
            }
        }
        Matrix e(2, 3, 1);
        e = c;
        assert(c == e && "Wrong matrix assignment\n");
        c = c;
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
/* Equal and unequal matrices -- operator ==, operator != */
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
        assert(a == b && !(a != b) && "Equal matrices marked as unequal\n");
        assert(!(a == c) && a != c && "Unequal matrices marked as equal\n");
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
    std::cout << "OK" << std::endl;
}

/* Test 7 */
/* Output -- operator << */
void test_out()
{
    print_test_number();
    try {
        Matrix a(3, 4);
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                a[i][j] = j - i + 1;
            }
        }
        std::stringstream file;
        file << a;
        Matrix b(3, 4);
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                file >> b[i][j];
            }
        }
        assert(a == b && "Wrong matrix output\n");
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 8 */
/* Operations Matrix op= Matrix */
void test_ops_mat_mat_1()
{
    print_test_number();
    try {
        Matrix a(3, 4, 12), b(3, 4, 7), c(3, 4, 3), cc(3, 4, 3), d(3, 4, 4);
        c += d;
        assert(c == b && "Wrong matrix sum\n");
        c -= d;
        assert(c == cc && "Wrong matrix substraction\n");
        c *= d;
        assert(c == a && "Wrong matrix element-by multiplication\n");
        c /= d;
        assert(c == cc && "Wrong matrix division\n");
        
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    try{
        Matrix q(3, 4, 5), p(4, 3, 2);
        q += p;
        assert("Undetected wrong matrix sum\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try{
        Matrix q(3, 4, 5), p(4, 3, 2);
        q -= p;
        assert("Undetected wrong matrix substracion\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try{
        Matrix q(3, 4, 5), p(4, 3, 2);
        q *= p;
        assert("Undetected wrong matrix multiplication\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try{
        Matrix q(3, 4, 5), p(4, 3, 2);
        q /= p;
        assert("Undetected wrong matrix division\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }    
    try {
        Matrix aa(3, 4, 12), bb(3, 4, 2), cc(3, 4, 3), dd(3, 4, 2);
        bb *= cc *= dd;
        assert(bb == aa && "Wrong matrix element-by multiplication\n");
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 9 */
/* Operations Matrix op Matrix */
void test_ops_mat_mat_2()
{
    print_test_number();
    try {
        Matrix a(3, 4, 12), b(3, 4, 7), c(3, 4, 3), d(3, 4, 4), e(3, 4, 1);
        Matrix res(3, 4);
        res = c + d;
        assert(res == b && "Wrong matrix sum\n");
        res = d - c;
        assert(res == e && "Wrong matrix substraction\n");
        res = c * d;
        assert(res == a && "Wrong matrix element-by multiplication\n");
        res = d / c;
        assert(res == e && "Wrong matrix division\n");
        
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    try{
        Matrix q(3, 4, 5), p(4, 3, 2);
        Matrix s = q + p;
        assert("Undetected wrong matrix sum\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try{
        Matrix q(3, 4, 5), p(4, 3, 2);
        Matrix s = q - p;
        assert("Undetected wrong matrix substracion\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try{
        Matrix q(3, 4, 5), p(4, 3, 2);
        Matrix s = q * p;
        assert("Undetected wrong matrix multiplication\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try{
        Matrix q(3, 4, 5), p(4, 3, 2);
        Matrix s = q / p;
        assert("Undetected wrong matrix division\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    std::cout << "OK" << std::endl;
}

/* Test 10 */
/* Operations Matrix op= Number */
void test_ops_mat_num_1()
{
    print_test_number();
    try {
        Matrix a(3, 4, 12), b(3, 4, 7), c(3, 4, 3), cc(3, 4, 3);
        int32_t d = 4;
        c += d;
        assert(c == b && "Wrong matrix sum\n");
        c -= d;
        assert(c == cc && "Wrong matrix substraction\n");
        c *= d;
        assert(c == a && "Wrong matrix element-by multiplication\n");
        c /= d;
        assert(c == cc && "Wrong matrix division\n");
        
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    try {
        Matrix a(2, 3, 2), b(2, 3, 3), c(2, 3, 9);
        int32_t d = 4;
        a += b += d;
        assert(a == c && "Wrong matrix sum\n");
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 11 */
/* Operations Matrix op Number */
void test_ops_mat_num_2()
{
    print_test_number();
    try {
        Matrix a(3, 4, 12), b(3, 4, 7), c(3, 4, 3), e(3, 4, -1), f(3, 4, 0);
        Matrix res(3, 4);
        int32_t d = 4;
        res = c + d;
        assert(res == b && "Wrong matrix sum\n");
        res = c - d;
        assert(res == e && "Wrong matrix substraction\n");
        res = c * d;
        assert(res == a && "Wrong matrix element-by multiplication\n");
        res = c / d;
        assert(res == f && "Wrong matrix division\n");
        
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 12 */
/* Operations Number op Matrix */
void test_ops_mat_num_3()
{
    print_test_number();
    try {
        Matrix a(3, 4, 12), b(3, 4, 7), c(3, 4, 3), e(3, 4, 1), res(3, 4);
        int32_t d = 4;
        res = d + c;
        assert(res == b && "Wrong matrix sum\n");
        res = d - c;
        assert(res == e && "Wrong matrix substraction\n");
        res = d * c;
        assert(res == a && "Wrong matrix element-by multiplication\n");
        res = d / c;
        assert(res == e && "Wrong matrix division\n");
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 13 */
/* Matrix transposition */
void test_transp()
{
    print_test_number();
    try {
        Matrix a(3, 4), b(4, 3), c(4, 4);
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                a[i][j] = b[j][i] = j - i;
            }
        }
        assert(a.transp() == b && "Wrong matrix transposition\n");
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                c[i][j] = j - i;
            }
        }
        Matrix d(c), t(c);
        d *= -1;
        c.transp();
        assert(!(t == c) && c == d && "Wrong matrix transposition\n");
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 14 */
/* Correct matrix multiplication */
void test_dot_correct()
{
    print_test_number();
    try {
        Matrix a(5, 4), b(4, 3), c(5, 3, 0);
        for (size_t i = 0; i < 5; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                a[i][j] = i + j;
            }
        }
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                b[i][j] = i - j;
            }
        }
        for (size_t i = 0; i < 5; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                for (size_t k = 0; k < 4; ++k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        assert(c == dot(a, b) && "Wrong matrix multiplication\n");
        Matrix e = dot(b, a);
    } catch (std::logic_error &ex) {
        assert(ex.what());
    }
    std::cout << "OK" << std::endl;
}

/* Test 15 */
/* Incorrect matrix multiplication */
void test_dot_incorrect()
{
    print_test_number();
    try {
        Matrix a(5, 4, 1), b(4, 3, 2);
        Matrix c = dot(b, a);
        std::cout << c;
        assert("Undetected incorrect matrix multiplication\n");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    std::cout << "OK" << std::endl;
}


int main() 
{
    test_shape();
    test_elem_correct();
    test_elem_incorrect();
    test_constructors_correct();
    test_constructors_incorrect();
    test_equation();
    test_out();
    test_ops_mat_mat_1();
    test_ops_mat_mat_2();
    test_ops_mat_num_1();
    test_ops_mat_num_2();
    test_ops_mat_num_3();
    test_transp();
    test_dot_correct();
    test_dot_incorrect();

    return 0;
}
