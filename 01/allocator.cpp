#include <cstddef>
#include "allocator.h"


Allocator::Allocator() = default;
Allocator::~Allocator() {
    delete[] head;
}
void Allocator::make_allocator(const size_t max_size) {
    if (max_size < off) {
        throw 1; /* new allocated memory is less than used memory */        
    } else if (max_size <= size) {
        len = max_size;
    } else {
        char *new_head = new char[max_size];
        for (size_t i = 0; i < off; ++i) {
            new_head[i] = head[i];
        }
        delete[] head;
        head = new_head;
        len = max_size;
        size = max_size;
    }
}
char *Allocator::alloc(const size_t size) {
    if (off + size <= len) {
        off += size;
        return head + off - size;
    } else {
        return nullptr;
    }
}
void Allocator::reset() {
    off = 0;
}

