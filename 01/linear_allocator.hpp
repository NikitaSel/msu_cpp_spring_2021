#pragma once
#include <cstddef>
#include <stdlib.h>
#include <new>
#include <iostream>


class LinearAllocator
{
public:
	LinearAllocator();
	~LinearAllocator();
	void makeAllocator(std::size_t maxSize);
	char* alloc(std::size_t size);
	void reset();

private:
	std::size_t totalSize = 0;
	std::size_t offset = 0;
	char* start_ptr = nullptr;
};
