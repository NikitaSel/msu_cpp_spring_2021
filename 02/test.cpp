#include "parser.hpp"

bool _num_callback_test=false;
bool _str_callback_test=false;
bool _start_callback_test=false;	
bool _end_callback_test=false;

void GlobalNumFunc(uint64_t){
	_num_callback_test = true;
}

void GlobalStrFunc(std::string){
	_str_callback_test = true;
}

void GlobalStartFunc(){
	_start_callback_test = true;	
}

void GlobalEndFunc(){
	_end_callback_test = true;	
}

void CallbackStartEndTest(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;

	Parser myParser;
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("0Callback1Start2End3Test4 12345");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"0Callback1Start2End3Test4", (uint64_t)12345};

	assert(returned_tokens == original_tokens);
	assert(!_num_callback_test);
	assert(!_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackStartEndTest Passed" << std::endl;
	
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackStrNumTest(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
	
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("0Callback1Str2Num3Test4 12345");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"0Callback1Str2Num3Test4", (uint64_t)12345};

	assert(returned_tokens == original_tokens);
	assert(_num_callback_test);
	assert(_str_callback_test);
	assert(!_start_callback_test);
	assert(!_end_callback_test);
	std::cout << "CallbackStrNumTest Passed" << std::endl;

	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackOnTest(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
	
	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("0Call1back2Str3Num4Start5End6Test7 12345");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"0Call1back2Str3Num4Start5End6Test7", (uint64_t)12345};

	assert(returned_tokens == original_tokens);
	assert(_num_callback_test);
	assert(_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackStrNumStartEndTest Passed" << std::endl;

	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackOffTest(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	Parser myParser;

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("0Callback1Off2Test3 12345");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"0Callback1Off2Test3", (uint64_t)12345};

	assert(returned_tokens == original_tokens);
	assert(!_num_callback_test);
	assert(!_str_callback_test);
	assert(!_start_callback_test);
	assert(!_end_callback_test);
	std::cout << "CallbackOffTest Passed" << std::endl;
}

void CallbackOnEmptyLineTest(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{};

	assert(returned_tokens == original_tokens);
	assert(!_num_callback_test);
	assert(!_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackOnEmptyLineTest Passed" <<std::endl;

	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackOnSpacesLineTest(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("    ");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{};
	assert(returned_tokens == original_tokens);
	assert(!_num_callback_test);
	assert(!_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackOnSpacesLineTest Passed" << std::endl;

	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackOnNumWithZerosTest(){	
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("00000000000000000000123");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{ (uint64_t)123};

	assert(returned_tokens == original_tokens);
	assert(_num_callback_test);
	assert(!_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackOnNumWithZerosTest Passed" <<std::endl;

	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackOnOneLetterTest(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("a");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"a"};

	assert(returned_tokens == original_tokens);
	assert(!_num_callback_test);
	assert(_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackOnOneLetterTest Passed" <<std::endl;

	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackOnOneNumberTest(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("1");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{(uint64_t)1};

	assert(returned_tokens == original_tokens);
	assert(_num_callback_test);
	assert(!_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackOnOneNumberTest Passed" <<std::endl;

	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackOnMaxNumTest1(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);
	
	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("18446744073709551616");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"18446744073709551616"};

	assert(returned_tokens == original_tokens);
	assert(!_num_callback_test);
	assert(_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackOnMaxNumTest1(2^64+1) Passed" << std::endl;

	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackOnMaxNumTest2(){
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("18446744073709551615");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{(uint64_t)18446744073709551615};

	assert(returned_tokens == original_tokens);
	assert(_num_callback_test);
	assert(!_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackOnMaxNumTest2(2^64) Passed" << std::endl;

	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;
}

void CallbackOnLongStringTest(){	
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

	void (*startPtr)() = GlobalStartFunc;
	void (*endPtr)() = GlobalEndFunc;
	void (*numPtr)(uint64_t) = GlobalNumFunc;
	void (*strPtr)(std::string) = GlobalStrFunc;

	Parser myParser;
	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);

	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("918274129324 1q q1 ejfbvejlqhvbceljahsvbc eljh 1§h4blj§1h4vjb1h34bj13h tr3 t1t");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{(uint64_t)918274129324, "1q", "q1", "ejfbvejlqhvbceljahsvbc", "eljh", "1§h4blj§1h4vjb1h34bj13h", "tr3", "t1t"};
	
	assert(returned_tokens == original_tokens);
	assert(_num_callback_test);
	assert(_str_callback_test);
	assert(_start_callback_test);
	assert(_end_callback_test);
	std::cout << "CallbackOnLongStringTest Passed" << std::endl;
	_num_callback_test = _str_callback_test = _start_callback_test = _end_callback_test = false;

}

int main(){

	CallbackStartEndTest();
	CallbackStrNumTest();
	CallbackOnTest();
	CallbackOffTest();
	CallbackOnEmptyLineTest();
	CallbackOnSpacesLineTest();
	CallbackOnNumWithZerosTest();
	CallbackOnOneLetterTest();
	CallbackOnOneNumberTest();
	CallbackOnMaxNumTest1();
	CallbackOnMaxNumTest2();
	CallbackOnLongStringTest();

	return 0;
}

