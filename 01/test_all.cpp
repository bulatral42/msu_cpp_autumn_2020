#include <iostream>
#include "allocator.h"

void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": ";
    ++n;
}

/* Test 1 */
/* One good alloc */
void test_ga() 
{
    print_test_number();
    Allocator heap;
    heap.make_allocator(10);
    char *p1 = heap.alloc(5);
    if (p1 == nullptr) {
        std::cout << "Wrong nullptr" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }
}

/* Test 2 */
/* Two good allocs */
void test_ga_ga()
{
    print_test_number();
    Allocator heap;
    heap.make_allocator(10);
    char *p1 = heap.alloc(5);
    char *p2 = heap.alloc(5);
    if (p1 == nullptr || p2 == nullptr) {
        std::cout << "Wrong nullptr" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }
}

/* Test 3 */
/* Bad alloc */
void test_ba()
{
    print_test_number();
    Allocator heap;
    heap.make_allocator(5);
    char *p1 = heap.alloc(6);
    if (p1 != nullptr) {
        std::cout << "Bad alloc" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }
}

/* Test 4 */
/* Bad alloc after good alloc */
void test_ga_ba()
{
    print_test_number();
    Allocator heap;
    heap.make_allocator(5);
    char *p1 = heap.alloc(3);
    *p1 = 'q';
    char *p2 = heap.alloc(3);
    if (p2 != nullptr) {
        std::cout << "Bad alloc" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }    
}

/* Test 5 */
/* Good alloc after reset */
void test_rs_ga()
{
    print_test_number();
    Allocator heap;
    heap.make_allocator(10);
    char *p1 = heap.alloc(5);
    heap.reset();
    p1 = heap.alloc(6);
    if (p1 == nullptr) {
        std::cout << "Wrong nullptr" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }   
}

/* Test 6 */
/* Bad alloc after reset */
void test_rs_ba()
{
    print_test_number();
    Allocator heap;
    heap.make_allocator(10);
    char *p1 = heap.alloc(5);
    heap.reset();
    p1 = heap.alloc(11);
    if (p1 != nullptr) {
        std::cout << "Bad alloc" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }   
}

/* Test 7 */
/* Valid reallocation to less size and good alloc */
void test_gra_ga()
{
    print_test_number();
    Allocator heap;
    heap.make_allocator(10);
    char *p1 = heap.alloc(5);
    heap.make_allocator(6);
    p1 = heap.alloc(1);
    if (p1 == nullptr) {
        std::cout << "Wrong nullptr" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }  
}

/* Test 8 */
/* Valid reallocation to less size and bad alloc */
void test_gra_ba()
{
    print_test_number();
    Allocator heap;
    heap.make_allocator(10);
    char *p1 = heap.alloc(5);
    heap.make_allocator(6);
    p1 = heap.alloc(2);
    if (p1 != nullptr) {
        std::cout << "Bad alloc" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }  
}

/* Test 9 */
/* Invalid reallocation to less size */
void test_bra()
{
    print_test_number();
    try {
        Allocator heap;
        heap.make_allocator(10);
        char *p1 = heap.alloc(5);
        p1[1] = 'q';
        heap.make_allocator(4);
        std::cout << "Attempt to set Allocator's memory to less than used";
    } catch (int err) {
        if (err == 1) {
            std::cout << "OK" << std::endl;
        }
    }
}


int main() 
{
    test_ga();
    test_ga_ga();
    test_ba();
    test_ga_ba();
    test_rs_ga();
    test_rs_ba();
    test_gra_ga();
    test_gra_ba();
    test_bra();
    return 0;
}
