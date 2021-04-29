#pragma once
#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer{

    static constexpr char Separator = ' ';
    std::ostream& out_;

public:
    explicit Serializer(std::ostream& out): out_(out){};

    template <class T>
    Error save(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT... args);

private:
    template <class T, class... ArgsT>
    Error process(T&& val, ArgsT&&... args);
    
    template <class T>
    Error process(T arg);

    Error process(bool& arg);
    Error process(uint64_t& arg);
};

class Deserializer{

    std::istream& in_;

public:
    explicit Deserializer(std::istream& in): in_(in){};

    template <class T>
    Error load(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT&... args);

private:
    template <class T, class... ArgsT>
    Error process(T&& val, ArgsT&&... args);
    
    template <class T>
    Error process(T& arg);

    Error process(bool& arg);
    Error process(uint64_t& arg);

};

#include "serializer.tpp"
