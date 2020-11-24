#pragma once

#include <cctype>
#include <exception>
#include <iostream>

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

constexpr int MAX_BLOCKS = 1024;

template<class T>
class Allocator
{
    struct Storage {
        T *ptrs[MAX_BLOCKS];
        size_t lens[MAX_BLOCKS];
    } storage;
    size_t n_blocks{0};

/*public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T&;
    using const_reference = const T &;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
*/
public:
    Allocator();
    ~Allocator();
    T *allocate(size_t);
    void deallocate(T *);
};

#include "allocator.tpp"

