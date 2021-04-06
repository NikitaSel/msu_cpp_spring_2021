#include "parser.hpp"

void StartFunc(){
	std::cout << "Сustom Callback For Start" << std::endl;
}

void EndFunc(){
	std::cout << "Custom Callback For End" << std::endl;
}

void NumFunc(uint64_t num){
	std::cout << "Custom Callback For Number =  " << num << std::endl;	
}

void StrFunc(std::string str){
	std::cout << "Custom Callback For Word = " << str << std::endl;
}

void CallbackOffTest(){	
	Parser myParser;
	std::cout << "\nCustom Callback Off" << std::endl;
	std::cout << "Text - techno1sphere2 12345" << std::endl;
	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("techno1sphere2 12345");
	uint64_t num = 12345;
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"techno1sphere2", num};
	assert(returned_tokens == original_tokens);
	std::cout << "Test1 Passed" << std::endl <<std::endl;
}

void CallbackOnDefaultTest(){
	void (*startPtr)() = StartFunc;
	void (*endPtr)() = EndFunc;

	void (*numPtr)(uint64_t) = NumFunc;
	void (*strPtr)(std::string) = StrFunc;

	Parser myParser;

	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);
	std::cout << "Custom Callback On" << std::endl;
	std::cout << "Text - techno1sphere2 12345" << std::endl;
	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("techno1sphere2 12345");
	uint64_t num = 12345;
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"techno1sphere2", num};
	assert(returned_tokens == original_tokens);
	std::cout << "Test2 Passed" << std::endl <<std::endl;
}

void EmptyLineTest(){
	Parser myParser;
	std::cout << "Custom Callback Off" << std::endl;
	std::cout << "Text - \"\"" << std::endl;
	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{};
	assert(returned_tokens == original_tokens);
	std::cout << "Test3 Passed" << std::endl <<std::endl;
}

void SpacesLineTest(){	
	Parser myParser;
	std::cout << "Custom Callback Off" << std::endl;
	std::cout << "Text - \"    \"" << std::endl;
	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("    ");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{};
	assert(returned_tokens == original_tokens);
	std::cout << "Test4 Passed" << std::endl <<std::endl;
}

void OneLetterTest(){
	Parser myParser;
	std::cout << "Custom Callback Off" << std::endl;
	std::cout << "Text - a" << std::endl;
	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("a");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"a"};
	assert(returned_tokens == original_tokens);
	std::cout << "Test5 Passed" << std::endl <<std::endl;
}

void OneNumberTest(){
	Parser myParser;
	std::cout << "Custom Callback Off" << std::endl;
	std::cout << "Text - 1" << std::endl;
	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("1");
	uint64_t num = 1;
	std::vector<std::variant<uint64_t, std::string>> original_tokens{num};
	assert(returned_tokens == original_tokens);
	std::cout << "Test6 Passed" << std::endl <<std::endl;
}

void MaxNumTest(){
	Parser myParser;
	std::cout << "Custom Callback Off" << std::endl;
	std::cout << "Text - 18446744073709551616 ==> (2^64+1)" << std::endl;
	std::vector<std::variant<uint64_t, std::string>> returned_tokens = myParser.MakeParse("18446744073709551616");
	std::vector<std::variant<uint64_t, std::string>> original_tokens{"18446744073709551616"};
	assert(returned_tokens == original_tokens);
	std::cout << "Test7 Passed" << std::endl <<std::endl;
}

int main(){

	CallbackOffTest();
	CallbackOnDefaultTest();
	EmptyLineTest();
	SpacesLineTest();
	OneLetterTest();
	OneNumberTest();
	MaxNumTest();

	return 0;
}

