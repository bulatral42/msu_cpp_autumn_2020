/* Test 9 */
/* Invalid reallocation to less size */

#include <iostream>
#include "allocator.h"

int main() {
    try {
        Allocator heap;
        heap.make_allocator(10);
        char *p1 = heap.alloc(5);
        p1[1] = 'q';
        heap.make_allocator(4);
    } catch (int err) {
        if (err == 1) {
            std::cout << "OK" << std::endl;
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
    std::cout <<  "Error: Not blocked attempt to set Allocator's memory to less than used" << std::endl;
    return 0;
}
