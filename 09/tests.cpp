#include <iostream>
#include <exception>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include "threadsort.hpp"


constexpr size_t N = 10000000;


void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": " << std::endl;
    ++n;
}


/* Test 1 */
/* 2 threads */
void test_th2() 
{
    print_test_number();
    try {
        std::string filename = "check1.bin";
        std::vector<uint64_t> vec;
        vec.reserve(N);
        std::ofstream file("check1.bin", std::ios::binary);
        for (size_t i = 0; i < N; ++i) {
            uint64_t tmp = std::rand();
            vec.push_back(tmp);
            file.write((char *)&tmp, sizeof(tmp));
        }
        file.close();

        threadsort("check1.bin", 2);
        std::sort(vec.begin(), vec.end());
        std::ifstream file2("check1.bin_res.bin", std::ios::binary);
        for (size_t i = 0; i < N; ++i) {
            uint64_t tmp;
            file2.read((char *)&tmp, sizeof(tmp));
            if (vec[i] != tmp) {
                std::cout << "Dismath at index " << i << std::endl;
                std::cout << vec[i] << " != " << tmp << std::endl;
                assert(0 && "Wrong sorting");
            }
        }
    } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
        assert(0 && "std::exception is caught");
    }
    std::cout << "Report: OK" << std::endl;
    remove("check1.bin");
    remove("check1.bin_res.bin");
}


/* Test 2 */
/* 8 threads */
void test_th8() 
{
    print_test_number();
    try {
        std::string filename = "check2.bin";
        std::vector<uint64_t> vec;
        vec.reserve(N);
        std::ofstream file("check2.bin", std::ios::binary);
        for (size_t i = 0; i < N; ++i) {
            uint64_t tmp = std::rand();
            file.write((char *)&tmp, sizeof(tmp));
            vec.push_back(tmp);
        }
        file.close();

        threadsort("check2.bin", 8);
        
        std::sort(vec.begin(), vec.end());
        std::ifstream file2("check2.bin_res.bin", std::ios::binary);
        for (size_t i = 0; i < N; ++i) {
            uint64_t tmp;
            file2.read((char *)&tmp, sizeof(tmp));
            if (vec[i] != tmp) {
                std::cout << "Dismath at index " << i << std::endl;
                std::cout << vec[i] << " != " << tmp << std::endl;
                assert(0 && "Wrong sorting");
            }
        }
    } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
        assert(0 && "std::exception is caught");
    }
    std::cout << "Report: OK" << std::endl;
    remove("check2.bin");
    remove("check2.bin_res.bin");
}


int main() 
{  
    test_th2();
    test_th8();
    return 0;
}
