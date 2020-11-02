CPP = g++
FLAGS = -O1 -Wall -std=c++17

all : tests.o big_int.o
	$(CPP) $(FLAGS) tests.o big_int.o -o tests

test: tests
	./tests

tests.o: tests.cpp
	$(CPP) $(FLAGS) tests.cpp -c -o tests.o

big_int.o: big_int.cpp
	$(CPP) $(FLAGS) big_int.cpp -c -o big_int.o

clean:
	rm *.o tests
