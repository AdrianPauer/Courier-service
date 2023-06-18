#include <iostream>
#include <fstream>
#include <iomanip>
#include "algorithm"
#include "1_Address.h"

//1.uloha
Address::Address() {
    postalCode = 0;
    country = "UNDEFINED";
}
std::string Address::removeSpaces(const std::string &word)const{
    std::string word1 = "";
    int firstIndex = 0;
    int lastIndex = word.size()-1;
    while(word[firstIndex] == ' ')
        firstIndex ++;
    while(word[lastIndex] == ' ')
        lastIndex --;
    for(firstIndex;firstIndex<=lastIndex;firstIndex++)
    {
        word1 += word[firstIndex];
    }

    return word1;
}
void Address::putAddress(const std::string &completeAdress){

    std::string completeAdress1 = removeSpaces(completeAdress);
    if(completeAdress1[5] >= '0' && completeAdress1[5] <= '9')
        throw WrongInput("WRONG POSTAL CODE");

    std::istringstream input{completeAdress1};
    char dash;
    int code;
    std:: string country1;
    input >> code;
    input>>dash;
    std::getline(input,country1);
    if (dash != '#')
        throw WrongInput("Address has wrong format");
    if (code > 100000 || code == 0)
        throw WrongInput("WRONG POSTAL CODE");
    std::string country1WithoutSpaces = removeSpaces(country1);
    if ( country1 == " ")
        throw WrongInput ("WRONG COUNTRY");
    for (char i : country1WithoutSpaces){
        if (! ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || i == ' ') )
            throw WrongInput ("WRONG COUNTRY");
    }
    postalCode = code;
    country = country1WithoutSpaces;
}
std::string Address::getAddress()const {
    std::ostringstream output;
    output<<std::setw(5) << std::setfill('0')<<std::to_string(postalCode)<<"#";
    output<<country;
    return output.str();
}


