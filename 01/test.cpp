#include <cstring>
#include "linear_allocator.hpp"
#include <cassert>

void TestSizeLimit(){
	LinearAllocator testAllocator;
	testAllocator.makeAllocator(20);
	testAllocator.alloc(5);
	assert(testAllocator.alloc(100) == nullptr);
	std::cout << "Test 1 Passed" << std::endl;
}

void TestReset1(){
	LinearAllocator testAllocator;
	testAllocator.makeAllocator(40);

	char *cut_1 = testAllocator.alloc(20);
	std::strncpy(cut_1, "ABABABABAB", 20);

	testAllocator.reset();

	char *cut_2 = testAllocator.alloc(20);
	assert(std::string(cut_1) == std::string(cut_2));
	std::cout << "Test 2 Passed" << std::endl;
}

void TestReset2(){
	LinearAllocator testAllocator;
	testAllocator.makeAllocator(10);

	char *cut_1 = testAllocator.alloc(5);
	std::strncpy(cut_1, "AAAAA", 5);

	char *cut_2 = testAllocator.alloc(3);
	std::strncpy(cut_2, "BB", 3);
	
	testAllocator.reset();

	assert(std::string(cut_1) == "AAAAABB");
	std::cout << "Test 3 Passed" << std::endl;
}

void TestMultipleAlloc(){	
	LinearAllocator testAllocator;
	testAllocator.makeAllocator(100);
	testAllocator.alloc(10);
	testAllocator.alloc(20);
	testAllocator.alloc(30);
	assert(testAllocator.alloc(40) != nullptr);
	std::cout << "Test 4 Passed" << std::endl;
}

void TestMultipleMakeAllocator(){
	LinearAllocator testAllocator;
	testAllocator.makeAllocator(10);
	testAllocator.alloc(1);

	testAllocator.makeAllocator(1000);
	assert(testAllocator.alloc(100) != nullptr);
	std::cout << "Test 5 Passed" << std::endl;
}

void TestPointer(){
	LinearAllocator testAllocator;
	testAllocator.makeAllocator(150);
	char *cut_1 = testAllocator.alloc(5);
	std::strncpy(cut_1, "ABCDE", 5);
	assert(*(cut_1 + 1) ==  char('B'));
	std::cout << "Test 6 Passed" << std::endl;
	
}

int main(){
	TestSizeLimit();
	TestReset1();
	TestReset2();
	TestMultipleAlloc();
	TestMultipleMakeAllocator();
	TestPointer();

	return 0;
	
}

