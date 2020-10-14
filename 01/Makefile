CPP = g++
FLAGS = -O1 -Wall -std=c++17

all : test_all.o allocator.o
	$(CPP) $(FLAGS) test_all.o allocator.o -o test_all

test: test_all
	./test_all

test_all.o: test_all.cpp
	$(CPP) $(FLAGS) test_all.cpp -c -o test_all.o

allocator.o: allocator.cpp
	$(CPP) $(FLAGS) allocator.cpp -c -o allocator.o

clean:
	rm -rf *.o test_all
