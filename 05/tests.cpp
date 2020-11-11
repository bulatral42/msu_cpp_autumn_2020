#include <iostream>
#include <exception>
#include <cassert>
#include <sstream>
#include "serializer.hpp"


struct DataOne
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a, b, c);
    }
    template <class Deserializer>
    Error deserialize(Deserializer &deserializer) {
        return deserializer(a, b, c);
    }
};


struct DataTwo
{
    uint64_t a;
    uint64_t b;
    bool c;

    template <class Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a, b, c);
    }
    template <class Deserializer>
    Error deserialize(Deserializer &deserializer) {
        return deserializer(a, b, c);
    }
};


struct DataThree
{
    uint64_t a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a, b);
    }
    template <class Deserializer>
    Error deserialize(Deserializer &deserializer) {
        return deserializer(a, b);
    }
};


struct BigData
{
    uint64_t a1, a2, a3, a4;
    bool b5, b6, b7;
    uint64_t a8, a9;
    bool b10;

    template <class Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a1, a2, a3, a4, b5, b6, b7, a8, a9, b10);
    }
    template <class Deserializer>
    Error deserialize(Deserializer &deserializer) {
        return deserializer(a1, a2, a3, a4, b5, b6, b7, a8, a9, b10);
    }
};


void print_test_number()
{
    static int n{1};
    std::cout << "Test " << n << ": " << std::endl;
    ++n;
}

/* Test 1 */
/* Serialize and deserialize one struct */
void test_one_struct() 
{
    print_test_number();
    try {
        DataOne x { 12, true, 34 };
        std::stringstream stream1;
        Serializer ser1(stream1);
        ser1.save(x);

        DataOne y { 0, false, 0 };
        Deserializer deser1(stream1);
        const Error err = deser1.load(y);

        assert(err == Error::NoError && "Incorrect return status");
        assert(x.a == y.a && x.b == y.b && x.c == y.c &&
               "Wrong (de)serialization");
    } catch(const std::exception &exc) {
        std::cout << exc.what() << std::endl;
        assert("Error!");
    }
    
    try {
        BigData x { 0, 1, 2, 3, false, true, true, 7, 8, false };
        std::stringstream stream2;
        Serializer ser2(stream2);
        ser2.save(x);

        BigData y { 10, 11, 12, 13, true, true, false, 17, 18, false };
        Deserializer deser2(stream2);
        const Error err = deser2.load(y);

        assert(err == Error::NoError && "Incorrect return status");
        assert(x.a1 == y.a1 && x.a2 == y.a2 && x.a3 == y.a3 && x.a4 == y.a4 &&
               x.b5 == y.b5 && x.b6 == y.b6 && x.b7 == y.b7 &&
               x.a8 == y.a8 && x.a9 == y.a9 &&
               x.b10 == y.b10 && "Wrong (de)serialization");
    } catch(const std::exception &exc) {
        std::cout << exc.what() << std::endl;
        assert("Error!");
    }
    std::cout << "Report: OK" << std::endl;
}

/* Test 2 */
/* Serialize one struct and deserialize it to different (not matching) struct */
void test_diff_structs() 
{
    print_test_number();
    try {
        DataOne x { 12, true, 34 };
        std::stringstream stream1;
        Serializer ser1(stream1);
        ser1.save(x);

        DataTwo y { 0, false, 0 };
        Deserializer deser1(stream1);
        const Error err = deser1.load(y);

        assert(err == Error::CorruptedArchive &&
               "Undetected wrong deserialization");
    } catch(const std::exception &exc) {
        std::cout << exc.what() << std::endl;
        assert("Error!");
    }
    std::cout << "Report: OK" << std::endl;
}


/* Test 3 */
/* Serialize one struct and deserialize it to matching struct (substruct) */
void test_substruct() 
{
    print_test_number();
    try {
        DataOne x { 12, true, 34 };
        std::stringstream stream1;
        Serializer ser1(stream1);
        ser1.save(x);

        DataThree y { 300, false };
        Deserializer deser1(stream1);
        const Error err = deser1.load(y);

        assert(err == Error::NoError && "Incorrect return status");
        assert(x.a == y.a && x.b == y.b && "Wrong (de)serialization");
    } catch(const std::exception &exc) {
        std::cout << exc.what() << std::endl;
        assert("Error!");
    }
    std::cout << "Report: OK" << std::endl;
}


int main() 
{
    test_one_struct();
    test_diff_structs();
    test_substruct();


    return 0;
}
