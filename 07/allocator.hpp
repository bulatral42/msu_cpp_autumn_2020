#pragma once

#include <cctype>
#include <exception>
#include <iostream>


constexpr int MAX_BLOCKS = 1024;

template<class T>
class MyAllocator
{
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
    MyAllocator() = default;
    ~MyAllocator() = default;
    T *allocate(size_t);
    void deallocate(T *, size_t);
    T *reallocate(T *, size_t, size_t);
};

#include "allocator.tpp"

