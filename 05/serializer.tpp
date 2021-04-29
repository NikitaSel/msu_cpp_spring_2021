#include "serializer.hpp"


template <class T>
Error Serializer::save(T& object)
{
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args){
    return process(args...);
}

template <class T>
Error Serializer::process(T arg){
    (void)arg;
    return Error::CorruptedArchive;
}

Error Serializer::process(bool& arg){
    // std::cout << "bool ";
    out_ << this->Separator << (arg ? "true" : "false");
    return Error::NoError;
}

Error Serializer::process(uint64_t& arg){
    // std::cout << "uint ";
    out_ << this->Separator << arg;
    return Error::NoError;
}

template <class T, class... ArgsT> 
Error Serializer::process(T&& val, ArgsT&&... args){
    Error retval = process(val);
    if (retval == Error::NoError)
        return process(std::forward<ArgsT>(args)...);
    return retval;
}

template <class T>
Error Deserializer::load(T& object){

    if (in_.peek() == EOF)
        return Error::CorruptedArchive;

    Error retval = object.deserialize(*this);

    if (in_.peek() == EOF){
        // std::cout << "1" << std::endl;
        return retval;}
    // std::cout << "2" << std::endl;
    return Error::CorruptedArchive;
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&... args){
    return process(args...);
}

template <class T>
Error Deserializer::process(T& arg){
    (void)arg;
    // std::cout << "3" << std::endl;
    return Error::CorruptedArchive;
}

Error Deserializer::process(bool& arg){
    // std::cout << "bool" << std::endl;
    std::string text;
    in_ >> text;

    if (text == "true")
        arg = true;
    else if (text == "false")
        arg = false;
    else
        return Error::CorruptedArchive;

    return Error::NoError;
}

Error Deserializer::process(uint64_t& arg){
    // std::cout << "uint64" << std::endl;
    std::string text;
    in_ >> text;

    try{

        arg = std::stoull(text);

    } catch(std::invalid_argument){ return Error::CorruptedArchive; }

    return Error::NoError;
}

template <class T, class... ArgsT>
Error Deserializer::process(T&& val, ArgsT&&... args){
    Error retval = process(val);
    if (retval == Error::NoError)
        return process(args...);
    return Error::CorruptedArchive;
}

