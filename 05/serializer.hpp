#pragma once

#include <cstddef>
#include <sstream>


enum class Error
{
    NoError,
    CorruptedArchive,
    SaveProblem
};


class Serializer
{
    static constexpr char SEP = ' ';
    std::ostream &out_;
public:
    explicit Serializer(std::ostream& out);

    template<class T>
    Error save(T &&object);

    template<class... ArgsT>
    Error operator()(ArgsT&&... args);
    
private:
    Error write_(bool val);
    Error write_(uint64_t val);
    
    template<class T>
    Error process_(T &&val);
    
    template<class T, class... ArgsT>
    Error process_(T &&val, ArgsT&&... args);
};


class Deserializer
{
    std::istream &in_;
    
public:
    explicit Deserializer(std::istream& in);

    template<class T>
    Error load(T &object);

    template<class... ArgsT>
    Error operator()(ArgsT&&... args);

private:
    Error read_(bool &val);
    Error read_(uint64_t &val);
    
    template<class T>
    Error process_(T &&val);
    
    template<class T, class... ArgsT>
    Error process_(T &&val, ArgsT&&... args);
};

#include "serializer.tpp"


