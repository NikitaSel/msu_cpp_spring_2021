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

void Parser::MakeParse(const char *line){
	if (startFP)
		(*startFP)();

	bool flag=false;
	std::string token;
	int i = 0;

	while (line[i] != '\0'){
		if (!isspace(line[i])){
			token += line[i];
			if (!isdigit(line[i])){
				flag=true;
			}
		} 
		else{
			if (flag){
				if (strFP) 
					(*strFP)(token);
			}
			else{
				if (numFP)  
					(*numFP)(stoi(token));
			}	
			flag=false;
			token.clear();
		}
		i++;
	} 
	if (flag){
		if (strFP) 
			(*strFP)(token);
	}
	else{
		if (numFP)  
			(*numFP)(stoi(token));
	}
	token.clear();
	if (endFP)
		(*endFP)();	
}	

