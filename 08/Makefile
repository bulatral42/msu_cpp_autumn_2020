CPP = g++
FLAGS = -O2 -Wall -g -std=c++17 -pthread

all : tests.o thread_pool.o thread_pool.tpp thread_pool.hpp
	$(CPP) $(FLAGS) tests.o thread_pool.o -o tests

test: all
	./tests

tests.o: tests.cpp
	$(CPP) $(FLAGS) tests.cpp -c -o tests.o

thread_pool.o:
	$(CPP) $(FLAGS) thread_pool.cpp -c -o thread_pool.o

#thread_pool: thread_pool.hpp thread_pool.tpp

clean:
	rm *.o tests
