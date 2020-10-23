#include <iostream>
#include <cinttypes>
#include <exception>
#include <functional>
#include "parser.h"

/* Exceptions */
Parser_exception::Parser_exception(const char *message) {
    int i = 0;
    for (; i < MAX_MSG_LEN && message[i]; ++i) {
        msg[i] = message[i];
    }
    ex_code = msg[0];
    msg[i] = 0;
}
Parser_exception::Parser_exception(int n) : ex_code{n} {}
int Parser_exception::code() const throw() {
    return ex_code;
}
const char* Parser_exception::what() const throw() {
    return msg;
}
Parser_exception::~Parser_exception() = default;


/* Warnings */
void warn_null_func() {
    std::cout << "Warning: Nullptr is set as function ptr" << std::endl;
} 


/* Default procedures */
void parser_start_default() {
    std::cout << "Parsing started..." << std::endl;
}
void parser_end_default(const Parser_stats &) {
    std::cout << "...parsing ended" << std::endl;
}
void parser_str_default(const std::string &s) {
    std::cout << "String: " << s << std::endl;
}
void parser_num_default(uint64_t n) {   
    std::cout << "Number: " << n << std::endl;
}

/* Parser methods */
Parser::Parser() = default;

Parser::~Parser() = default;

std::string Parser::get_token(std::string::const_iterator &it, 
                              const std::string::const_iterator &it_end) {
    while(it != it_end && isspace(*it)) {
        ++it;
    }
    auto it1 = it, it2 = it;
    for (; it2 != it_end && !isspace(*it2); ++it2) {}
    it = it2;
    return std::string(it1, it2); 
}

void Parser::set_start_callback(void_f func) {
    if (func == nullptr) {
        warn_null_func();
    }
    start = func;
}

void Parser::set_end_callback(end_procedure func) {
    if (func == nullptr) {
        warn_null_func();
    }
    end = func; 
}

void Parser::set_number_callback(num_procedure func) {
    if (func == nullptr) {
        warn_null_func();
    }
    num_handler = func;
}

void Parser::set_string_callback(str_procedure func) {
    if (func == nullptr) {
        warn_null_func();
    }
    str_handler = func;
}

void Parser::string_callback(const std::string &str) {
    ++stats.strings;
    if (str_handler == nullptr) {
        throw Parser_exception("Nullptr is not callable");
    }
    str_handler(str);
}

void Parser::number_callback(uint64_t num) {
    ++stats.strings;
    if (num_handler == nullptr) {
        throw Parser_exception("Nullptr is not callable");
    }
    num_handler(num);
}

bool Parser::is_number(const std::string &token) const {
    bool num_flag{true};
    for (auto &it2 : token) {
        if (!(num_flag = isdigit(it2))) {
            break;
        }
    }
    return num_flag;
}

void Parser::operator()(const std::string &text) {
    if (start == nullptr) {
        throw Parser_exception("Nullptr is not callable");
    }
    start();
    for (auto it = text.cbegin(), it_end = text.cend(); it != it_end; ++it) {
        std::string token = get_token(it, it_end);        
        if (token.empty()) {
            end(stats);
            return;
        }
        ++stats.tokens;
        if (is_number(token)) {
            try {
                uint64_t num = std::stoull(token);
                number_callback(num);
            } catch (std::logic_error &le) {
                string_callback(token);            
            }
        } else {
            string_callback(token);
        }
        if (it == it_end) { /* Last token ended at the end of text */
            break;
        }
    }
    if (end == nullptr) {
        throw Parser_exception("Nullptr is not callable");
    }
    end(stats);
}

