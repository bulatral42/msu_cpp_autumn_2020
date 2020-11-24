#pragma once

#include <sstream>
#include <cctype>
#include <exception>
#include "allocator.hpp"


constexpr int SCALER = 2;


template<class T, class Allocator = MyAllocator<T>>
class Vector
{
    T *head_{nullptr};
    size_t size_{0}, capacity_{0};
    Allocator alloc;
    
public:
    Vector(size_t);
    Vector(size_t, const T&);
    Vector(const Vector &);
    Vector(Vector &&);
    ~Vector();
    
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

