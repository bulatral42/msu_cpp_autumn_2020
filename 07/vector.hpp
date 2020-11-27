#pragma once

#include "allocator.hpp"
#include "iterator.hpp"

constexpr size_t SCALER = 2;


template<class T, class Allocator = MyAllocator<T>>
class Vector
{
    T *head_{nullptr};
    size_t size_{0}, capacity_{0};
    Allocator alloc;
    
public:
    using value_type = T;
    
    Vector(size_t size = 8);
    Vector(size_t, const T&);
    Vector(const Vector &);
    Vector(Vector &&);
    ~Vector();
    
    Vector &operator =(const Vector &);
    Vector &operator =(Vector &&);
    
    const T operator [](const size_t) const;
    T &operator [](const size_t);
    
    void push_back(const T &);
    void push_back(T &&);
    void pop_back();
    template<class... ArgsT>
    const T &emplace_back(ArgsT&&...);
    
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    
    void clear();
    void resize(size_t);
    void resize(size_t, const T &);
    void reserve(size_t);
    
    bool operator ==(const Vector &) const;
    bool operator !=(const Vector &) const;
    
    Iterator<Vector<T, Allocator>> begin();
    Iterator<Vector<T, Allocator>> end();
    ReverseIterator<Vector<T, Allocator>> rbegin();
    ReverseIterator<Vector<T, Allocator>> rend();
  
};


#include "vector.tpp"

