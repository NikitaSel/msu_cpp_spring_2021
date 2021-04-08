CC=g++

FLAGS=-std=c++17 -O2 -Wall -fsanitize=address -pedantic -Wextra

all: parser.o test.o
	$(CC) $(FLAGS) parser.o test.o -o test_file

parser.o: parser.cpp parser.hpp
	$(CC) $(FLAGS) parser.cpp -c

test.o: test.cpp parser.hpp
	$(CC) $(FLAGS) test.cpp -c

clean:
	rm -f *.o test_file

test: 
	./test_file

