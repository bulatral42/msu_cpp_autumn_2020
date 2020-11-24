CPP = g++
FLAGS = -O2 -Wall -std=c++17

all : tests.o
	$(CPP) $(FLAGS) tests.o -o tests

test: tests
	./tests

tests.o: tests.cpp
	$(CPP) $(FLAGS) tests.cpp -c -o tests.o

allocator: allocator.tpp

iterator: iterator.tpp

vector: vector.tpp

clean:
	rm *.o tests
