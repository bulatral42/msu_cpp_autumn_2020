/* Test 4 */
/* Bad alloc after good alloc */

#include <iostream>
#include "allocator.h"

int main() {
    try {
        Allocator heap;
        heap.make_allocator(5);
        char *p1 = heap.alloc(3);
        *p1 = 'q';
        char *p2 = heap.alloc(3);
        if (p2 != nullptr) {
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
        return 0;
    } 
    std::cout << "OK" << std::endl;
    return 0;
}
