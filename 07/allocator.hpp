#pragma once

constexpr int MAX_BLOCKS = 1024;

template<class T>
class MyAllocator
{

public:
    MyAllocator() = default;
    ~MyAllocator() = default;
    T *allocate(size_t);
    void deallocate(T *, size_t);
    T *reallocate(T *, size_t, size_t);
};

#include "allocator.tpp"

