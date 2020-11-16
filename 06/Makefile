CPP = g++
FLAGS = -O1 -Wall -std=c++17

all : tests.o
	$(CPP) $(FLAGS) tests.o format.o -o tests

test: tests
	./tests

tests.o: tests.cpp format.o format.tpp
	$(CPP) $(FLAGS) tests.cpp -c -o tests.o

format.o: format.cpp
	$(CPP) $(FLAGS) format.cpp -c -o format.o
clean:
	rm *.o tests
