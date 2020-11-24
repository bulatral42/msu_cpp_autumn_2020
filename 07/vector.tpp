

/*
template<class T, class Allocator>
Vector<T, Allocator>::
*/

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t size) : 
        head_{alloc.allocate(SCALER * size)}, 
        size_{size}, capacity_{SCALER * size} {}
template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t size, const T &val) : 
        head_{alloc.allocate(SCALER * size)}, 
        size_{size}, capacity_{SCALER * size} {
    for (size_t i = 0; i < size_; ++i) {
        head_[i] = val;
    }
}
template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector &other) : 
        head_{alloc.allocate(other.capacity_)}, 
        size_{other.size_}, capacity_{other.capacity_} {}
template<class T, class Allocator>
Vector<T, Allocator>::Vector(Vector &&other) : 
        head_{std::move(other.head_)}, size_{std::move(other.size_)},
        capacity_{std::move(other.capacity_)} {
    other.head_ = nullptr;
    other.size_ = other.capacity_ = 0;
}
template<class T, class Allocator>
Vector<T, Allocator>::~Vector() {
    alloc.deallocate(head_, capacity_);
}

template<class T, class Allocator>
const T Vector<T, Allocator>::operator [](const size_t idx) const {
    if (idx < 0 || idx >= size_) {
        throw std::out_of_range("Invalid index");
    }
    return head_[idx];
}

template<class T, class Allocator>
T &Vector<T, Allocator>::operator [](const size_t idx) {
    if (idx < 0 || idx >= size_) {
        throw std::out_of_range("Invalid index");
    }
    return head_[idx];
}
/*
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
    */
    
