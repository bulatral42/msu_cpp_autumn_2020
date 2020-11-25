/* Constructors and destructior */
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

/* Indexing */
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

/* Push, emplace, pop */
template<class T, class Allocator>
void Vector<T, Allocator>::push_back(const T &obj) {
    if (capacity_ == size_) {
        size_t new_cap = capacity_ == 0 ? 8 : SCALER * capacity_;
        head_ = alloc.reallocate(head_, capacity_, new_cap);
        capacity_ = new_cap;
    }
    head_[size_++] = obj;
}

template<class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
    if (size_ == 0) {
        throw std::out_of_range("Pop from empty Vector");
    }
    --size_;
}

template<class T, class Allocator>
void Vector<T, Allocator>::emplace_back(T &&obj) {
    if (capacity_ == size_) {
        size_t new_cap = capacity_ == 0 ? 8 : SCALER * capacity_;
        head_ = alloc.reallocate(head_, capacity_, new_cap);
        capacity_ = new_cap;
    }

    head_[size_++] = std::move(obj);
}

/* Stats */
template<class T, class Allocator>
bool Vector<T, Allocator>::empty() const {
    return size_ == 0;
}

template<class T, class Allocator>
size_t Vector<T, Allocator>::size() const {
    return size_;
}

template<class T, class Allocator>
size_t Vector<T, Allocator>::capacity() const {
    return capacity_;
}

/* Clear, resize, reserve */
template<class T, class Allocator>
void Vector<T, Allocator>::clear() {
    size_ = 0;
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_t new_size) {
    if (new_size > capacity_) {
        head_ = alloc.reallocate(head_, capacity_, new_size);
        capacity_ = new_size;
    }
    size_ = new_size;
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_t new_size, const T &obj) {
    if (new_size > capacity_) {
        head_ = alloc.reallocate(head_, capacity_, new_size);
        capacity_ = new_size;
    }
    for (size_t i = size_; i < new_size; ++i) {
        head_[i] = obj;
    }
    size_ = new_size;
}

template<class T, class Allocator>
void Vector<T, Allocator>::reserve(size_t new_cap) {
    if (new_cap > capacity_) {
        head_ = alloc.reallocate(head_, capacity_, new_cap);
        capacity_ = new_cap;
    }
}

/* Iterators */
template<class T, class Allocator>
Iterator<Vector<T, Allocator>> Vector<T, Allocator>::begin() {
    return Iterator<Vector<T, Allocator>>(head_);
}

template<class T, class Allocator>
Iterator<Vector<T, Allocator>> Vector<T, Allocator>::end() {
    return Iterator<Vector<T, Allocator>>(head_ + size_);
}

template<class T, class Allocator>
ReverseIterator<Vector<T, Allocator>> Vector<T, Allocator>::rbegin() {
    return ReverseIterator<Vector<T, Allocator>>(head_ + size_ - 1);
}

template<class T, class Allocator>
ReverseIterator<Vector<T, Allocator>> Vector<T, Allocator>::rend() {
    return ReverseIterator<Vector<T, Allocator>>(head_ - 1);
}

