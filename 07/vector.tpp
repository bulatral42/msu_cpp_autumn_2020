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
        size_{other.size_}, capacity_{other.capacity_} {
    for (size_t i = 0; i < size_; ++i) {
        head_[i] = other.head_[i];
    }
}

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

/* Assignment */
template<class T, class Allocator>
Vector<T, Allocator> &Vector<T, Allocator>::operator =(const Vector &other) {
    if (this == &other) {
        return *this;
    }
    T *tmp = alloc.allocate(other.capacity_);
    for (size_t i = 0; i < other.size_; ++i) {
        tmp[i] = other.head_[i];
    }
    alloc.deallocate(head_, capacity_);
    head_ = tmp;
    size_ = other.size_;
    capacity_ = other.capacity_;
    return *this;
}

template<class T, class Allocator>
Vector<T, Allocator> &Vector<T, Allocator>::operator =(Vector &&other) {
    if (this == &other) {
        return *this;
    }
    head_ = std::move(other.head_);
    size_ = std::move(other.size_);
    capacity_ = std::move(other.capacity_);
    other.head_ = nullptr;
    other.size_ = other.capacity_ = 0;
    return *this;
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
void Vector<T, Allocator>::push_back(T &&obj) {
    if (capacity_ == size_) {
        size_t new_cap = capacity_ == 0 ? 8 : SCALER * capacity_;
        head_ = alloc.reallocate(head_, capacity_, new_cap);
        capacity_ = new_cap;
    }
    head_[size_++] = std::move(obj);
}

template<class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
    if (size_ == 0) {
        throw std::out_of_range("Pop from empty Vector");
    }
    --size_;
}

template<class T, class Allocator>
template<class... ArgsT>
const T &Vector<T, Allocator>::emplace_back(ArgsT&&... args) {
    if (capacity_ == size_) {
        size_t new_cap = capacity_ == 0 ? 8 : SCALER * capacity_;
        head_ = alloc.reallocate(head_, capacity_, new_cap);
        capacity_ = new_cap;
    }
    T *emp_ptr = head_ + size_;
    emp_ptr->~T();
    new(emp_ptr) T{std::forward<ArgsT>(args)...};
    ++size_;
    return *emp_ptr;
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

/* Comperisons */
template<class T, class Allocator>
bool Vector<T, Allocator>::operator ==(const Vector &other) const {
    if(other.size_ != size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (head_[i] != other.head_[i]) {
            return false;
        }
    }
    return true;
}

template<class T, class Allocator>
bool Vector<T, Allocator>::operator !=(const Vector &other) const {
    return !(*this == other);
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

