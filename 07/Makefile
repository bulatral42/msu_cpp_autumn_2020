CPP = g++
FLAGS = -O2 -Wall -g -std=c++17

all : tests.o
	$(CPP) $(FLAGS) tests.o -o tests

test: all
	./tests

tests.o: tests.cpp vector allocator iterator
	$(CPP) $(FLAGS) tests.cpp -c -o tests.o

allocator: allocator.hpp allocator.tpp

iterator: iterator.hpp iterator.tpp

vector: vector.hpp vector.tpp

clean:
	rm *.o tests
