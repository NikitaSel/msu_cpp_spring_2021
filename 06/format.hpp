#pragma once 
#include <iostream>
#include <exception>
#include "sstream"
#include "vector"

struct FormatError: public std::exception
{
	const char * what () const throw ()
    {
    	return "invalid format";
    }
};

std::string format(std::string&& formatstring);

template <class... ArgT>
std::string format(std::string&& formatstring, ArgT&&... args);

class Formatter
{
private:
    std::string& formatstring;
    std::vector<std::string> elements;
    
public:
    Formatter(std::string& formatstring): formatstring(formatstring) {};
    ~Formatter(){};

    template <class... ArgT>
    std::string validate(ArgT&&... args);

    template<class T>
    void format(T&& arg);

    template <class T, class... ArgT>
    void format(T&& arg, ArgT&&... args);
};

#include "format.tpp"
