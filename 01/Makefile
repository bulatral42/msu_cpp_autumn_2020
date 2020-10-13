CPP = g++
FLAGS = -O1 -Wall -std=c++17

all : test_all.cpp allocator.o
	$(CPP) $(FLAGS) test_all.cpp allocator.o -o test_all

test: test_all
	./test_all

allocator.o: allocator.cpp
	$(CPP) $(FLAGS) allocator.cpp -c -o allocator.o

clean:
	rm -rf *.o test_all
