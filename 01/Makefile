CPP = g++
FLAGS = -O1 -Wall -std=c++17
TESTS = test_1 test_2 test_3 test_4 test_5 test_6 test_7 test_8 test_9

all : test clean

test: $(TESTS)
	./test_1
	./test_2
	./test_3
	./test_4
	./test_5
	./test_6
	./test_7
	./test_8
	./test_9

test_1: test_1.cpp allocator.o
	$(CPP) $(FLAGS) test_1.cpp allocator.o -o test_1

test_2: test_2.cpp allocator.o
	$(CPP) $(FLAGS) test_2.cpp allocator.o -o test_2

test_3: test_3.cpp allocator.o
	$(CPP) $(FLAGS) test_3.cpp allocator.o -o test_3

test_4: test_4.cpp allocator.o
	$(CPP) $(FLAGS) test_4.cpp allocator.o -o test_4

test_5: test_5.cpp allocator.o
	$(CPP) $(FLAGS) test_5.cpp allocator.o -o test_5

test_6: test_6.cpp allocator.o
	$(CPP) $(FLAGS) test_6.cpp allocator.o -o test_6

test_7: test_7.cpp allocator.o
	$(CPP) $(FLAGS) test_7.cpp allocator.o -o test_7

test_8: test_8.cpp allocator.o
	$(CPP) $(FLAGS) test_8.cpp allocator.o -o test_8

test_9: test_9.cpp allocator.o
	$(CPP) $(FLAGS) test_9.cpp allocator.o -o test_9



allocator.o: allocator.cpp
	$(CPP) $(FLAGS) allocator.cpp -c -o allocator.o

clean:
	rm -rf *.o $(TESTS)
