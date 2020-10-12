/* Test 8 */
/* Valid reallocation to less size and bad alloc */

#include <iostream>
#include "allocator.h"

int main() {
    try {
        Allocator heap;
        heap.make_allocator(10);
        char *p1 = heap.alloc(5);
        heap.make_allocator(6);
        p1 = heap.alloc(2);
        if (p1 != nullptr) {
            throw "Bad alloc";
        }
    } catch (int err) {
        if (err == 1) {
            std::cout << "Error: Attempt to set Allocator's memory to less than used" << std::endl;
        } else {
            std::cout << "Error: Code_" << err << std::endl;
        }
        return 0;
    }
    catch (const char *msg) {
        std::cout <<"Error: " << msg << std::endl;
        return 0;
    } catch (...) {
        std::cout <<"Error: Unknown" << std::endl;
    } 
    std::cout << "OK" << std::endl;
    return 0;
}
