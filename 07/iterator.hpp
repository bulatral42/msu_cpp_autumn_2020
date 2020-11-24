#pragma once

#include <string>
#include <sstream>
#include <cctype>
#include <exception>


/* Exceptions */
constexpr int MAX_MSG_LEN = 255;  /* Exception message buffer size */

struct format_exception : std::exception {
    format_exception(const char *);
    const char* what() const noexcept override;
    ~format_exception();
private:
    char msg_[MAX_MSG_LEN + 1] = { 0 };
};


struct format_index_error : format_exception {
    format_index_error(const char *);
    ~format_index_error();
};

struct format_argument_error : format_exception {
    format_argument_error(const char *);
    ~format_argument_error();
};




#include "vector.tpp"

