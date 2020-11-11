CPP = g++
FLAGS = -O1 -Wall -std=c++17

all : tests.o
	$(CPP) $(FLAGS) tests.o -o tests

test: tests
	./tests

tests.o: tests.cpp
	$(CPP) $(FLAGS) tests.cpp -c -o tests.o

clean:
	rm *.o tests
