std::string format(std::string&& formatstring){
    Formatter formatter(formatstring);
    return formatter.validate();
}

template <class... ArgT>
std::string format(std::string&& formatstring, ArgT&&... args){
    Formatter formatter(formatstring);
    formatter.format(args...);
    return formatter.validate(args...);
}

template<class T>
void Formatter::format(T&& arg){
    std::stringstream conv;
    conv << arg;
    this->elements.push_back(conv.str());
}

template<class T, class... ArgT>
void Formatter::format(T&& arg, ArgT&&... args){
    std::stringstream conv;
    conv << arg;
    this->elements.push_back(conv.str());
    format(std::forward<ArgT>(args)...);
}

template<class... ArgT>
std::string Formatter::validate(ArgT&&... args){
    uint32_t argsnumber = sizeof...(args);
    bool in_brackets = false;
    bool has_number = false;
    std::string retval;
    std::string ind;

    for (size_t i = 0; i < this->formatstring.length(); i++){

        if (in_brackets){
            if (this->formatstring[i] != '}' && !isdigit(this->formatstring[i]))
                throw FormatError();

            if (this->formatstring[i] == '{')
                throw FormatError();
            
            if (this->formatstring[i] != '}')
                has_number = true;

            ind += this->formatstring[i];
        }

        if (this->formatstring[i] == '{')
            in_brackets = true;

        if (!in_brackets)
            retval += this->formatstring[i];

        if (this->formatstring[i] == '}'){
            if (!in_brackets)
                throw FormatError();

            if (!has_number)
                throw FormatError();

            has_number = false;
            in_brackets = false;
            if (std::stol(ind) >= argsnumber)
                throw FormatError();

            retval += elements[std::stoul(ind)];
            ind = "";
        }
    }
    return retval;
}
