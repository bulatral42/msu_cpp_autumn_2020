#pragma once

class Allocator
{
    size_t size{}, off{}, len{};
    char *head{nullptr};
public:
    Allocator();
    ~Allocator();
    void make_allocator(const size_t max_size);
    char* alloc(const size_t size);
    void reset();    
};

