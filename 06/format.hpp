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


/* Main operations */
void set_at_zero(const std::string &, const std::string &,
                 std::string &, bool last_flag = false);


/* Template wrappers */
template<class T>
std::string format(const std::string &, const T &);

template<class T, class... ArgsT>
std::string format(const std::string &, const T &, const ArgsT&...);


#include "format.tpp"

