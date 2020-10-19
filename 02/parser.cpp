#include <iostream>
#include <iterator>
#include <cctype>
#include "parser.h"

void parser_start_default() {
    std::cout << "Parsing started" << std::endl;
}
void parser_end_default() {
    std::cout << "Parsing ended successfuly" << std::endl;
}

    std::string Parser::get_token(std::string::const_iterator &it, 
                                  std::string::const_iterator &it_end) {
        while(it != it_end && isspace(*it)) {
            ++it;
        }
        auto it1 = it, it2 = it;
        for (; it2 != it_end && !isspace(*it2); ++it2) {}
        it = it2;
        return it1 != it2 ? std::string(it1, it2) : std::string(" ");
    }
    
    Parser::Parser() = default;
    Parser::~Parser() = default;
    void Parser::set_start_callback(void_f func) {
        start = func;
    }
    void Parser::set_end_callback(void_f func) {
        end = func; 
    }
    void Parser::set_number_callback(num_procedure func) {
        num_handler = func;
    }
    void Parser::set_string_callback(str_procedure func) {
        str_handler = func;
    }
    bool Parser::is_number(const std::string &token) {
        bool num_flag{true};
        for (auto &it2 : token) {
            if (!(num_flag = isdigit(it2))) {
                break;
            }
        }
        return num_flag;
    }
    
    void Parser::operator()(const std::string &text) {
        start();
        for (auto it = text.cbegin(), it_end = text.cend(); it != it_end; ++it) {
            std::string token = get_token(it, it_end);
            if (token[0] == ' ') {
                end();
                return;
            }
            if (is_number(token)) {
                uint64_t num;
                sscanf(token.c_str(), "%" SCNu64, &num);
                num_handler(num);
            } else {
                str_handler(token);
            }
        }
        end();
    }
    
