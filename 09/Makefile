CPP = g++
FLAGS = -O2 -Wall -std=c++17 -pthread

all : tests.o threadsort.o
	$(CPP) $(FLAGS) tests.o threadsort.o -o tests

test: tests
	./tests

tests.o: tests.cpp
	$(CPP) $(FLAGS) tests.cpp -c -o tests.o

threadsort.o: threadsort.cpp
	$(CPP) $(FLAGS) threadsort.cpp -c -o threadsort.o

clean:
	rm *.o tests
