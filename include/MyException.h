#pragma once
#include <exception>
#include <string>


class MyException : public std::exception
{
private:
    std::string error;
    int value;
public:
    MyException(const char* error, int val) : error(error), value(val) {};
    std::string GetError() { return error; }
    int GetVal() { return value; }
};