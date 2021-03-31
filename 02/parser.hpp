#pragma once
#include <iostream>
#include <functional>
#include <utility>
#include <cstdlib>

class Parser{
public:
	using TypeStartEnd = void(*)();
	using TypeNum = void(*)(int);
	using TypeStr = void(*)(std::string);
	
	Parser();

	~Parser();

	void SetStartCallback(TypeStartEnd startPtr=nullptr);
	
	void SetEndCallback(TypeStartEnd endPtr=nullptr);

	void SetNumCallback(TypeNum numPtr=nullptr);

	void SetStrCallback(TypeStr strPtr=nullptr);

	void MakeParse(const char *line);

private:
	TypeStartEnd startFP = nullptr, endFP = nullptr;
	TypeNum  numFP = nullptr;
	TypeStr strFP = nullptr;
};


