#pragma once
#include <iostream>
#include <sstream>

//1.úloha
class WrongInput : public std::exception {
    std::string text;
public:
    WrongInput(const char *v) { text = v; };
    std::string message() const { return text; };
};

class Address{
    int  postalCode;
    std::string country;
public:
    Address();
    void putAddress(const std::string &completeAdress);
    std::string removeSpaces( const std::string &word)const;
    std::string getAddress()const;
};



