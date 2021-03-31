#include "parser.hpp"

void StartFunc(){
	std::cout << "Сustom Callback For Start" << std::endl;
}

void EndFunc(){
	std::cout << "Custom Callback For End" << std::endl;
}

void NumFunc(int num){
	std::cout << "Custom Callback For Number =  " << num << std::endl;
}

void StrFunc(std::string str){
	std::cout << "Custom Callback For Word = " << str << std::endl;
}

int main(){
	std::streambuf *out;
	void (*startPtr)() = StartFunc;
	void (*endPtr)() = EndFunc;
	void (*numPtr)(int) = NumFunc;
	void (*strPtr)(std::string) = StrFunc;

	Parser myParser1;

	std::cout << "Cuctom Callback Off" << std::endl;
	std::cout << std::endl;

	std::cout << "Text = i love pdf12 123" << std::endl;
	myParser1.MakeParse("i love pdf12 123");
	std::cout << std::endl;

	Parser myParser;

	myParser.SetStartCallback(startPtr);
	myParser.SetEndCallback(endPtr);
	myParser.SetNumCallback(numPtr);
	myParser.SetStrCallback(strPtr);

	std::cout << "Cuctom Callback On" << std::endl;
	std::cout << std::endl;

	std::cout << "Text = ilovepdf" << std::endl;
	myParser.MakeParse("ilovepdf");
	std::cout << std::endl;
	
	std::cout << "Text = ilove1234pdf" << std::endl;
	myParser.MakeParse("ilove1234pdf");
	std::cout << std::endl;

	std::cout << "Text = 123" << std::endl;
	myParser.MakeParse("123");
	std::cout << std::endl;

	std::cout << "Text = i love pdf12 123" << std::endl;
	myParser.MakeParse("i love pdf12 123");
	std::cout << std::endl;

	return 0;
}

