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

/* Test 1 */
/* Output to stream and to_string method */
void test_out_to_string() 
{
    print_test_number();
    try {
        BigInt a(123), b(-456), c(0), d;
        assert(a.to_string() == "123" && "Wrong conversion to string");
        assert(b.to_string() == "-456" && "Wrong conversion to string");
        assert(c.to_string() == "0" && "Wrong conversion to string");
        assert(d.to_string() == "0" && "Wrong conversion to string");
        std::ostringstream s;
        s << a << " " << b << " " << c << " " << d;
        std::string ans("123 -456 0 0");
        assert(ans == s.str() && "Wrong output to stream");
    } catch (std::logic_error &ex) {
        std::cout << ex.what() << std::endl;
        assert("std::logic_error is caught");
    }
    std::cout << "OK" << std::endl;
}


/* Test 2 */
/* Comparison operators */
void test_compare() 
{
    print_test_number();
    try {
        BigInt a1("123456789"), a2("123456789"), b("129456789");
        BigInt c1("-1000"), c2("-1000"), d("-1010");
        
        assert(a1 == a2 && "Invalid comparison");
        assert(!(a1 != a2) && "Invalid comparison");
        assert(a1 <= a2 && "Invalid comparison");
        assert(a1 >= a2 && "Invalid comparison");
        assert(!(a1 < a2) && "Invalid comparison");
        assert(!(a1 > a2) && "Invalid comparison");
        
        assert(!(a1 == b) && "Invalid comparison");
        assert(a1 != b && "Invalid comparison");
        assert(a1 < b && "Invalid comparison");
        assert(!(a1 > b) && "Invalid comparison");
        assert(a1 <= b && "Invalid comparison");
        assert(!(a1 >= b) && "Invalid comparison");
        
        assert(c1 == c2 && "Invalid comparison");
        assert(!(c1 != c2) && "Invalid comparison");
        assert(c1 <= c2 && "Invalid comparison");
        assert(c1 >= c2 && "Invalid comparison");
        assert(!(c1 < c2) && "Invalid comparison");
        assert(!(c1 > c2) && "Invalid comparison");
        
        assert(!(c1 == d) && "Invalid comparison");
        assert(c1 != d && "Invalid comparison");
        assert(c1 > d && "Invalid comparison");
        assert(!(c1 < d) && "Invalid comparison");
        assert(c1 >= d && "Invalid comparison");
        assert(!(c1 <= d) && "Invalid comparison");
        
        assert(a1 > d && a1 >= d && !(a1 < d) && "Invalid comparison");       
    } catch (std::logic_error &ex) {
        std::cout << ex.what() << std::endl;
        assert("std::logic_error is caught");
    }
    std::cout << "OK" << std::endl;
}


/* Test 3 */
/* Constructor from string */
void test_from_string() 
{
    print_test_number();
    try {
        BigInt a(123), b(-456), c(0), d(0), e(0), f(0), g(128), h(-256);
        BigInt aa("  \t 123 "), bb(" \n -456 "), cc("0"), dd("  -0 ");
        BigInt ee("  -0000"), ff("00000 "), gg("+000128"), hh("-0000256");
        BigInt ii("12345678910111213141516");      
        assert(a == aa && "Wrong conversion from string");
        assert(b == bb && "Wrong conversion from string");
        assert(c == cc && "Wrong conversion from string");
        assert(d == dd && "Wrong conversion from string");
        assert(e == ee && "Wrong conversion from string");
        assert(f == ff && "Wrong conversion from string");
        assert(g == gg && "Wrong conversion from string");
        assert(h == hh && "Wrong conversion from string");
        assert(ii.to_string() == "12345678910111213141516" && 
               "Wrong conversion from string");
    } catch (std::logic_error &ex) {
        std::cout << ex.what() << std::endl;
        assert("std::logic_error is caught");
    }
    try {
        BigInt a("   q123");
        std::cout << a;
        assert("Undetected invalid conversion from string");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try {
        BigInt a(" -q123");
        std::cout << a;
        assert("Undetected invalid conversion from string");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    std::cout << "OK" << std::endl;
}


/* Test 4 */
/* Copy and move constructors and operators */
void test_copy_move() 
{
    print_test_number();
    try {
        BigInt a(123), b(-456), c("-1235467890"), d(300);
        BigInt a2(123), b2(-456), c2("-1235467890"), d2(300);
        BigInt aa(a), bb(std::move(b));
        BigInt cc, dd;
        cc = c;
        dd = std::move(d); 
        assert(aa == a2 && a == a2 && "Wrong copy constructor");
        assert(bb == b2 && b.get_len() == 0 && "Wrong move constructor");
        assert(cc == c2 && c == c2 && "Wrong copy operator");
        assert(dd == d2 && d.get_len() == 0 && "Wrong move operator");
    } catch (std::logic_error &ex) {
        std::cout << ex.what() << std::endl;
        assert("std::logic_error is caught");
    }
    try {
        BigInt a("123");
        BigInt b(std::move(a));
        std::cout << b;
        assert("Undetected invalid conversion from string");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    try {
        BigInt a("123");
        BigInt b;
        b = std::move(a);
        std::cout << b;
        assert("Undetected invalid conversion from string");
    } catch (std::logic_error &ex) {
        std::cout << "Correct logic_error detected: " << ex.what() << std::endl;
    }
    std::cout << "OK" << std::endl;
}


/* Test 5 */
/* Addition */
void test_add() 
{
    print_test_number();
    try {
        /* True answers are taken from python3 inerpreter */
        BigInt a1("123456788765432112345678"), b1("876543211234567887654321");
        BigInt c1("999999999999999999999999");
        BigInt d1(a1);
        d1 += b1;        
        assert(d1 == c1 && a1 + b1 == c1 && b1 + a1 == c1 && "Wrong addition");

        BigInt a2("654456654"), b2("987654321");
        BigInt c2("1642110975");
        BigInt d2(a2);
        d2 += b2;        
        assert(d2 == c2 && b2 + a2 == c2 && a2 + b2 == c2 && "Wrong addition");
        
        BigInt a3("9999999999"), b3("1");
        BigInt c3("10000000000");
        BigInt d3(a3);
        d3 += b3;        
        assert(d3 == c3 && b3 + a3 == c3 && a3 + b3 == c3 && "Wrong addition");
        
        BigInt a4("123908"), b4("-919");
        BigInt c4("122989");
        BigInt d4(a4);
        d4 += b4;        
        assert(d4 == c4 && b4 + a4 == c4 && a4 + b4 == c4 && "Wrong addition");
        
        BigInt a5("-123908"), b5("919");
        BigInt c5("-122989");
        BigInt d5(a5);
        d5 += b5;        
        assert(d5 == c5 && b5 + a5 == c5 && a5 + b5 == c5 && "Wrong addition");
        
        BigInt a6("-123908"), b6("-919");
        BigInt c6("-124827");
        BigInt d6(a6);
        d6 += b6;        
        assert(d6 == c6 && b6 + a6 == c6 && a6 + b6 == c6 && "Wrong addition");
    } catch (std::logic_error &ex) {
        std::cout << ex.what() << std::endl;
        assert("std::logic_error is caught");
    }
    std::cout << "OK" << std::endl;
}


/* Test 6 */
/* Substraction */
void test_sub() 
{
    print_test_number();
    try {
        /* True answers are taken from python3 inerpreter */
        BigInt a1("123456788765432112345678"), b1("-876543211234567887654321");
        BigInt c1("999999999999999999999999");
        BigInt d1(a1);
        d1 -= b1;        
        assert(d1 == c1 && a1 - b1 == c1 && b1 - a1 == c1 && "Wrong substraction");

        BigInt a2("654456654"), b2("-987654321");
        BigInt c2("1642110975");
        BigInt d2(a2);
        d2 -= b2;        
        assert(d2 == c2 && b2 - a2 == c2 && a2 - b2 == c2 && "Wrong substraction");
        
        BigInt a3("9999999999"), b3("-1");
        BigInt c3("10000000000");
        BigInt d3(a3);
        d3 -= b3;        
        assert(d3 == c3 && b3 - a3 == c3 && a3 - b3 == c3 && "Wrong substraction");
        
        BigInt a4("123908"), b4("919");
        BigInt c4("122989");
        BigInt d4(a4);
        d4 -= b4;        
        assert(d4 == c4 && b4 - a4 == c4 && a4 - b4 == c4 && "Wrong substraction");
        
        BigInt a5("-123908"), b5("-919");
        BigInt c5("-122989");
        BigInt d5(a5);
        d5 -= b5;        
        assert(d5 == c5 && b5 - a5 == c5 && a5 - b5 == c5 && "Wrong substraction");
        
        BigInt a6("-123908"), b6("919");
        BigInt c6("-124827");
        BigInt d6(a6);
        d6 -= b6;        
        assert(d6 == c6 && b6 - a6 == c6 && a6 - b6 == c6 && "Wrong substraction");
    } catch (std::logic_error &ex) {
        std::cout << ex.what() << std::endl;
        assert("std::logic_error is caught");
    }
    std::cout << "OK" << std::endl;
}


/* Test 7 */
/* Multiplication */
void test_mult() 
{
    print_test_number();
    try {
        /* True answers are taken from python3 inerpreter */
        BigInt a1("123456788765432112345678"), b1("876543211234567887654321");
        BigInt c1("108215210073159587715286454808716607224522374638");
        BigInt d1(a1);
        d1 *= b1;        
        assert(d1 == c1 && a1 * b1 == c1 && b1 * a1 == c1 && "Wrong multiplication");

        BigInt a2("123456788765432112345678"), b2("-876543211234567887654321");
        BigInt c2("-108215210073159587715286454808716607224522374638");
        BigInt d2(a2);
        d2 *= b2;        
        assert(d2 == c2 && b2 * a2 == c2 && a2 * b2 == c2 && "Wrong multiplication");
        
        BigInt a3("-123456788765432112345678"), b3("-876543211234567887654321");
        BigInt c3("-108215210073159587715286454808716607224522374638");
        BigInt d3(a3);
        d3 *= b3;        
        assert(d3 == c3 && b3 * a3 == c3 && a3 * b3 == c3 && "Wrong multiplication");
        
        BigInt a4("999999999999"), b4("-1");
        BigInt c4("-999999999999");
        BigInt d4(a4);
        d4 *= b4;        
        assert(d4 == c4 && b4 * a4 == c4 && a4 * b4 == c4 && "Wrong multiplication");
        
        BigInt a5("123456789"), b5("1000000000");
        BigInt c5("123456789000000000");
        BigInt d5(a5);
        d5 *= b5;        
        assert(d5 == c5 && b5 * a5 == c5 && a5 * b5 == c5 && "Wrong multiplication");
        
        BigInt a6("-123908"), b6("0");
        BigInt c6("0");
        BigInt d6(a6);
        d6 *= b6;        
        assert(d6 == c6 && b6 * a6 == c6 && a6 * b6 == c6 && "Wrong multiplication");
        
        BigInt mega("999999999999999999999999999999999999999999");  /* 42 */
        std::string ans1("999999999999999999999999999999999999999998");
        std::string ans2("000000000000000000000000000000000000000001");
        BigInt megamega(ans1 + ans2);
        assert(mega * mega == megamega && "Wrong multiplication");
    } catch (std::logic_error &ex) {
        std::cout << ex.what() << std::endl;
        assert("std::logic_error is caught");
    }
    std::cout << "OK" << std::endl;
}


/* Test 7 */
/* Unary minus */
void test_u_minus() {
    print_test_number();
    try {
        BigInt a("123"), b(-123), c(0);
        assert(-a == b && -b == a && "Wrong unary minus");
        assert(-c == c && "Wrong unary minus");
    } catch (std::logic_error &ex) {
        std::cout << ex.what() << std::endl;
        assert("std::logic_error is caught");
    }
    std::cout << "OK" << std::endl;
}


int main() 
{
    test_out_to_string();
    test_compare();
    test_from_string();
    test_copy_move();
    test_add();
    test_sub();
    test_mult();
    test_u_minus();
    return 0;
}
