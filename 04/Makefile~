CPP = g++
FLAGS = -O1 -Wall -std=c++17

all : tests.o matrix.o
	$(CPP) $(FLAGS) tests.o matrix.o -o tests

test: tests
	./tests

tests.o: tests.cpp
	$(CPP) $(FLAGS) tests.cpp -c -o tests.o

parser.o: parser.cpp
	$(CPP) $(FLAGS) matrix.cpp -c -o matrix.o

clean:
	rm *.o tests
