#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <cassert>
#include <sstream>
#include "parser.h"


void my_start() {
    std::cout << "START!" << std::endl;
}
void my_end(const Parser_stats &stats) {    
    std::cout << "END! " << stats.strings << " strings, "; 
    std::cout << stats.numbers << " numbers\n" << std::endl;
}
void my_num(uint64_t num) {
    std::cout << "Number: " << num << std::endl;
}
void my_str(const std::string &line) {
    std::cout << "String: " << line << std::endl;
}

void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": ";
    ++n;
}

/* Test 1 */
/* Default sets */
void test_def_sets() 
{
    print_test_number();
    try {
        Parser my_parser;
        my_parser(" 1\tab a1\r ");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }
}

/* Test 2 */
/* User sets callbacks */
void test_usr_sets() 
{
    print_test_number();
    try {
        Parser my_parser;my_parser.set_number_callback(my_num);
        my_parser.set_string_callback(my_str);
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser(" 1000 \tab a1\r 23 ");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }
}

/* Test 3 */
/* Nullptr is set to strings (warning) but no call is made */
void test_usr_null_set_no_call_str() 
{
    print_test_number();
    try {
        Parser my_parser;
        std::vector<uint64_t> v_num;
        std::vector<std::string> v_str;
        my_parser.set_string_callback(nullptr);
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser(" 1\t1\r2323 ");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }
    
}

/* Test 4 */
/* Nullptr is set to nimbers (warning) but no call is made */
void test_usr_null_set_no_call_num() 
{
    print_test_number();
    try {
        Parser my_parser;
        std::vector<uint64_t> v_num;
        std::vector<std::string> v_str;
        my_parser.set_number_callback(nullptr);
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser(" abc ");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }  
}

/* Test 5 */
/* Nullptr is set to numbers (warning) and called -- exception is thrown */
void test_usr_null_set_call() 
{
    print_test_number();
    try {
        Parser my_parser;
        std::vector<uint64_t> v_num;
        std::vector<std::string> v_str;
        my_parser.set_number_callback(nullptr);
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser(" abc 12 ");
        assert(0 && "Attempt to call nullptr");
    } catch (Parser_exception &ex) {
        assert(ex.code() == 'N' && "Called nullptr is undetected");
    }  
}

/* Test 6 */
/* Parsing numbers */
void test_parse_nums() 
{
    print_test_number();
    try {
        Parser my_parser;
        std::vector<uint64_t> v_num, ans{ 1, 12, 132, 0 , 0 };
        std::vector<std::string> v_str;
        my_parser.set_number_callback([&](uint64_t x) { v_num.push_back(x); });
        my_parser.set_string_callback([&](std::string x) { v_str.push_back(x); });
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser(" 1  \n 12\r 00132\t 00 0  ");
        assert(ans == v_num && "Not all numbers are parsed\n");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }
    
}

/* Test 7 */
/* Parsing strings */
void test_parse_strs() 
{
    print_test_number();
    try {
        Parser my_parser;
        std::vector<uint64_t> v_num;
        std::vector<std::string> v_str, ans{ "-1", "qq", "AAA", "b122", "cc2c", "0xFF" };
        my_parser.set_number_callback([&](uint64_t x) { v_num.push_back(x); });
        my_parser.set_string_callback([&](std::string x) { v_str.push_back(x); });
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser(" -1   qq  AAA \n\n b122 cc2c \t0xFF");
        assert(ans == v_str && "Not all strings are parsed\n");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }
    
}

/* Test 8 */
/* Parsing strings and numbers */
void test_parse_mix() 
{
    print_test_number();
    try {
        Parser my_parser;
        std::vector<uint64_t> v_num, ans_num{ 132, 45, 0, 1212 };
        std::vector<std::string> v_str, ans_str{ "fggf", ";::", "-10", "ak0am", "-0", 
                "5ad", "asd12", "12a0", "A" };
        my_parser.set_number_callback([&](uint64_t x) { v_num.push_back(x); });
        my_parser.set_string_callback([&](std::string x) { v_str.push_back(x); });
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser("fggf 132 \t\t  ;:: 0045 -10 ak0am -0 5ad \rasd12 12a0 0000 \n A 1212 \n\n");
        assert(ans_str == v_str && ans_num == v_num && 
                "Not all strings or numbers are parsed\n");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }
    
}

/* Test 9 */
/* Parsing empty input */
void test_parse_empty() 
{
    print_test_number();
    try {
        Parser my_parser;
        std::vector<uint64_t> v_num;
        std::vector<std::string> v_str;
        my_parser.set_number_callback([&](uint64_t x) { v_num.push_back(x); });
        my_parser.set_string_callback([&](std::string x) { v_str.push_back(x); });
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser("");
        assert(v_str.empty() && v_num.empty() && "Too many strings or nimbers\n");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }
    
}

/* Test 10 */
/* Parsing only spaced input */
void test_parse_spaced() 
{
    print_test_number();
    try {
        Parser my_parser;
        std::vector<uint64_t> v_num;
        std::vector<std::string> v_str;
        my_parser.set_number_callback([&](uint64_t x) { v_num.push_back(x); });
        my_parser.set_string_callback([&](std::string x) { v_str.push_back(x); });
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser("  \n  \r \t   \t \n");
        assert(v_str.empty() && v_num.empty() && "Too many strings or nimbers\n");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }
    
}

/* Test 11 */
/* Parsing max allowed number */
void test_parse_maxnum() 
{
    print_test_number();
    try {
        uint64_t max = -1;
        std::stringstream line;
        line << max;
        std::string max_str = line.str();
        Parser my_parser;
        std::vector<uint64_t> v_num, ans_num{ max };
        std::vector<std::string> v_str;
        my_parser.set_number_callback([&](uint64_t x) { v_num.push_back(x); });
        my_parser.set_string_callback([&](std::string x) { v_str.push_back(x); });
        my_parser.set_start_callback(my_start);
        my_parser.set_end_callback(my_end);
        my_parser(max_str);
        assert(v_str.empty() && ans_num == v_num && "Wrong numbers parsing\n");
    } catch (Parser_exception &ex) {
        assert(ex.code() && ex.what());
    }
    
}


int main() 
{
    test_def_sets();
    test_usr_sets();
    test_usr_null_set_no_call_str();
    test_usr_null_set_no_call_num();
    test_usr_null_set_call();
    test_parse_nums();
    test_parse_strs();
    test_parse_mix();
    test_parse_empty();
    test_parse_spaced();
    test_parse_maxnum();
    
    return 0;
}
