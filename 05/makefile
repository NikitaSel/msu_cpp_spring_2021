CC=g++

FLAGS=-std=c++17 -Wall -pedantic -Wextra -fsanitize=address

all: 
	$(CC) $(FLAGS) test.cpp -o test_file

clean:
	rm -f *.o test_file

test: 
	./test_file
