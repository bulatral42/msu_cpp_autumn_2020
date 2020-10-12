#include <iostream>

class Allocator
{
    size_t size{}, off{}, len{};  /* size=heap_size , len=valid_length, off=offset*/
    char *head{nullptr};       /* always true: size >= len*/
public:
    Allocator() = default;
    ~Allocator() {
        delete[] head;
    }
    void make_allocator(size_t max_size) {
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
    char* alloc(size_t size) {
        if (head != nullptr && off + size <= len) {
            off += size;
            return head + off - size;
        } else {
            return nullptr;
        }
    }
    void reset() {
        off = 0;
    }
    void info() const {
        std::cout << "Size:   " << size << std::endl;
        std::cout << "Length: " << len << std::endl;
        std::cout << "Offset: " << off << std::endl;
    }    
};

int main() {
    try {
        Allocator heap;
        
    } catch (int err) {
        
    }
    Allocator heap;
    heap.make_allocator(10);
    heap.info();
    heap.make_allocator(5);
    heap.info();
    heap.make_allocator(7);
    heap.info();
    heap.make_allocator(11);
    heap.info();
    return 0;
}
