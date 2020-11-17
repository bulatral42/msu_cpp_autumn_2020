#include "format.hpp"


/* Exceptions */
format_exception::format_exception(const char *message) {
    int i = 0;
    for (; i < MAX_MSG_LEN && message[i]; ++i) {
        msg_[i] = message[i];
    }
    msg_[i] = 0;
}
const char* format_exception::what() const noexcept {
    return msg_;
}
format_exception::~format_exception() = default;

format_index_error::format_index_error(const char *msg) :
        format_exception{msg} {};
format_index_error::~format_index_error() = default;

format_argument_error::format_argument_error(const char *msg) :
        format_exception{msg} {};
format_argument_error::~format_argument_error() = default;


void set_at_zero(const std::string &fmt, const std::string &ptrn, 
                 std::string &res, bool last_flag)
{
    for (auto it1 = fmt.cbegin(); it1 != fmt.cend();) {
        auto it2 = it1;
        for (;it2 != fmt.cend() && *it2 != '{'; ++it2) {}
        if (it2 == fmt.cend()) {
            res.append(it1, it2);
            return;
        }
        
        if (it2 != it1) {  /* chars between '}' and '{' */
            res.append(it1, it2);
        }
        
        it1 = it2;
        for (it2 = it1 + 1; it2 != fmt.cend() && std::isdigit(*it2); ++it2) {}
        if (it2 == it1 + 1) {  /* No digit after '{' */
            throw format_index_error("Empty or corrupted index");
        }
        if (it2 == fmt.cend()) {
            throw format_index_error("No closing parenthesis");
        }

        if (*it2 != '}') {
            throw format_index_error("Corrupted index");
        }
        unsigned int idx{0};
        try {
            idx = std::stoul(std::string(it1 + 1, it2));
        } catch(std::logic_error &exc) {
            throw format_index_error("Corrupted index");
        }
        if (idx == 0) {
            res.append(ptrn);
        } else if (!last_flag) {
            std::ostringstream tmp;
            tmp << '{' << idx - 1 << '}';
            res.append(tmp.str());
        } else {  /* Nonzero index but just 1 argument left */
            throw format_argument_error("No argument for substitution");
        }
        it1 = it2 + 1;
    }
}
