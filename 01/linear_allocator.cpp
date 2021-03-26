#include "linear_allocator.hpp"


LinearAllocator::LinearAllocator(){}

LinearAllocator::~LinearAllocator(){
	delete[] start_ptr;
}

void LinearAllocator::makeAllocator(std::size_t maxSize){
	delete[] start_ptr;
	start_ptr = nullptr;

	start_ptr = new char[maxSize]; 
	offset = 0;
	totalSize=maxSize;
}

char* LinearAllocator::alloc(std::size_t size){ 
	if ((offset + size > totalSize) || (start_ptr == nullptr)){
		return nullptr; 
	}
	char* curr_address = start_ptr + offset;
	offset += size;
	
	return curr_address;
}

void LinearAllocator::reset(){
	offset = 0;
}

