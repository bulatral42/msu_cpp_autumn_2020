#pragma once

#include <sstream>
#include <cctype>
#include <exception>
#include "allocator.hpp"


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


template<class T, class Allocator = Allocator<T>>
class Vector
{
    T *head{nullptr};
    size_t size_{0}, capacity_{0};
    
public:
    const T operator [](const size_t) const;
    T &operator [](const size_t);
    void push_back(const T&);
    T pop_back();
    template<class... ArgsT>
    void emplace_back(ArgsT&&...);
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void clear();
    void resize(size_t);
    void resize(size_t, const T &);
    void reserve(size_t);
    
    /*
    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();
    */
};


#include "vector.tpp"

