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
	std::string token;
	size_t i = 0;
	
	do{
		if ((!isspace(line[i])) && (line[i] != '\0')){
			token += line[i];
			is_empty=false;
			if (!isdigit(line[i])){
				is_str=true;
			}
		} 
		else{
			if (!is_empty){
				if (!is_str){
					try{
						tokens.push_back(std::stoull(token));	
						if (numFP)
							numFP(std::stoull(token));
					}
					catch (...){is_str=true;}
				}
				if (is_str){
					tokens.push_back(token);
					if (strFP)
						strFP(token);	
				}
			token.clear();
			is_str=false;
			}
		}
		i++;
	} while(line[i-1] != '\0');

	if (endFP)
		endFP();

	return tokens;
}	

