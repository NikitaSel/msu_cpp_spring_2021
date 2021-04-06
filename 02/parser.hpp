#pragma once
#include <iostream>
#include <functional>
#include <utility>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <variant>
#include <string>

class Parser{
public:
	using TypeStartEnd = void(*)();
	using TypeNum = void(*)(uint64_t);
	using TypeStr = void(*)(std::string);
	
	Parser();

	~Parser();

	void SetStartCallback(TypeStartEnd startPtr=nullptr);
	
	void SetEndCallback(TypeStartEnd endPtr=nullptr);

	void SetNumCallback(TypeNum numPtr=nullptr);

	void SetStrCallback(TypeStr strPtr=nullptr);

	std::vector<std::variant<uint64_t, std::string>> MakeParse(const std::string &line);

private:
	TypeStartEnd startFP = nullptr, endFP = nullptr;
	TypeNum  numFP = nullptr;
	TypeStr strFP = nullptr;
};

