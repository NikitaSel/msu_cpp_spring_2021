#include "parser.hpp"

Parser::Parser(){}

Parser::~Parser(){}

void Parser::SetStartCallback(TypeStartEnd startPtr){
	startFP = startPtr;
}

void Parser::SetEndCallback(TypeStartEnd endPtr){
	endFP = endPtr;
}

void Parser::SetNumCallback(TypeNum numPtr){
	numFP = numPtr;
}

void Parser::SetStrCallback(TypeStr strPtr){
	strFP = strPtr;
}

std::vector<std::variant<uint64_t, std::string>> Parser::MakeParse(const std::string  &line){
	
	std::vector<std::variant<uint64_t, std::string>> tokens;

	if (startFP)
		startFP();

	bool is_str=false;
	bool is_empty=true;
	bool digtok_more_digmax = false;
	std::string token;
	std::string  maxNum = std::to_string(std::numeric_limits<uint64_t>::max());
	int max_len = maxNum.length();
	size_t i = 0;
	
	do{
		if ((!isspace(line[i])) & (line[i] != '\0')){
			token += line[i];
			if (!isdigit(line[i])){
				is_str=true;
			}
			else{
				digtok_more_digmax=true;
			}
			is_empty=false;
		} 
		else{
			if (!is_empty){
				if ((!is_str) & ((token.length() < max_len) ||
				                ((token.length() == max_len) & (!digtok_more_digmax)))){
					tokens.push_back(std::stoull(token));
					if (numFP)  
						numFP(std::stoull(token));
				}
				else{
					tokens.push_back(token);
					if (strFP) 
						strFP(token);
				}
			is_str=false;
			token.clear();
			}
		}
		i++;
	} while(line[i-1] != '\0');

	if (endFP)
		endFP();

	return tokens;
}	

