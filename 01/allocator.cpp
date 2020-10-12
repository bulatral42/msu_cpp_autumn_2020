#include <iostream>

class Allocator
{
    size_t size{}, off{}, len{};  /* size=heap_size , len=valid_length, off=offset*/
    char *head{nullptr};       /* always true: size >= len*/
public:
    Allocator(size_t size = 4 * sizeof(char)) : size{size} {}
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
        if (off + size <= len) {
            off += size;
            return head + (off - size) * sizeof(char);
        } else {
            return nullptr;
        }
    }
    void reset() {
        off = 0;
    }
    void info() {
        std::cout << "Size:   " << size << std::endl;
        std::cout << "Length: " << len << std::endl;
        std::cout << "Offset: " << off << std::endl;
    }
    
};

int main() {
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
