CPP = g++
FLAGS = -O1 -Wall -std=c++17

all : tests.o parser.o
	$(CPP) $(FLAGS) tests.o parser.o -o tests

test: tests
	./tests

tests.o: tests.cpp
	$(CPP) $(FLAGS) tests.cpp -c -o tests.o

parser.o: parser.cpp
	$(CPP) $(FLAGS) parser.cpp -c -o parser.o

clean:
	rm *.o tests
