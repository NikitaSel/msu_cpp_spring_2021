CC=g++

FLAGS=-std=c++17 -Wall -pedantic -Wextra

all: BigInt.o main.o 
	 $(CC) $(FLAGS) BigInt.o main.o -o test_file

BigInt.o: BigInt.cpp BigInt.hpp
	$(CC) $(FLAGS) BigInt.cpp -c

main.o: main.cpp BigInt.hpp
	$(CC) $(FLAGS) main.cpp -c

clean:
	rm -f *.o test_file

test: 
	./test_file
