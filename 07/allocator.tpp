template<class T>
Allocator<T>::Allocator() {
   for (size_t i = 0; i < MAX_BLOCKS; ++i) {
        storage.ptrs[i] = nullptr;
        storage.lens[i] = 0;
    }
}

template<class T>
Allocator<T>::~Allocator() {
    if (n_blocks != 0) {
        std::cout << "ERROR: " << n_blocks << " left!" << std::endl;
    }
    for (size_t i = 0; i < MAX_BLOCKS; ++i) {
        deallocate(storage.ptrs[i], storage.lens[i]);
    }
}    

template<class T>
T *Allocator<T>::allocate(size_t n_obj) {
    if (n_blocks == MAX_BLOCKS) {
        std::cout << "No memory" << std::endl;
        return nullptr;
    }
    T *ptr = new T[n_obj];
    if (ptr == nullptr) {
        std::cout << "No memory" << std::endl;
        return nullptr;
    }
    for (size_t i = 0; i < MAX_BLOCKS; ++i) {
        if (storage.ptrs[i] == nullptr) {
            storage.ptrs[i] = ptr;
            storage.lens[i] = n_obj;
            ++n_blocks;
        }
    }
    return ptr;
}

template<class T>
void Allocator<T>::deallocate(T *ptr) {
    if (ptr == nullptr) {
        return;
    }
    for (size_t i = 0; i < MAX_BLOCKS; ++i) {
        if (storage.ptrs[i] == ptr) {
            if (storage.lens[i] > 1) {
                delete[] ptr;
            } else {
                delete ptr;
            }
            storage.ptrs[i] = nullptr;
            storage.lens[i] = 0;
            --n_blocks;
            return;
        }
    }
    throw std::logic_error("Deaalocationg unallocated ptr");
}

