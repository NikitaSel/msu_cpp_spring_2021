CC=g++

FLAGS=-std=c++17 -O2 -Wall -fsanitize=address -pedantic -Wextra

all: matrix.o main.o 
	 $(CC) $(FLAGS) matrix.o main.o -o test_file

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) matrix.cpp -c

main.o: main.cpp matrix.hpp
	$(CC) $(FLAGS) main.cpp -c

clean:
	rm -f *.o test_file

test: 
	./test_file

