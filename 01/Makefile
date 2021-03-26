CC=g++

FLAGS=-std=c++17 -O2 -Wall -Werror -fsanitize=address -pedantic -Wextra

all: linear_allocator.o test.o
	$(CC) $(FLAGS) linear_allocator.o test.o -o test_

linear_allocator.o: linear_allocator.cpp linear_allocator.hpp
	$(CC) $(FLAGS) linear_allocator.cpp -c

test.o: test.cpp linear_allocator.hpp
	$(CC) $(FLAGS) test.cpp -c

clean:
	rm -f *.o test

test: test_
	./test
