template<class T>
T *MyAllocator<T>::allocate(size_t n_obj) {
    T *ptr = new T[n_obj];
    return ptr;
}

template<class T>
void MyAllocator<T>::deallocate(T *ptr, size_t size) {
    if (ptr == nullptr) {
        return;
    }
    if (size > 1) {
        delete[] ptr;
    } else {
        delete ptr;
    }
}

template<class T>
T *MyAllocator<T>::reallocate(T *old_ptr, size_t old_size, size_t new_size) {
    T *new_ptr = new T[new_size];
    if (old_ptr == nullptr) {
        old_size = 0;
    }
    for (size_t i = 0; i < new_size; ++i) {
        new_ptr[i] = old_ptr[i];
    }
    deallocate(old_ptr, old_size);
    return new_ptr;
}

