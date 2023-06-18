#include <fstream>
#include "algorithm"
#include <iostream>

#include "2_Package.h"

Package::Package(const std::string &package){
    if (!putPackage(package))
    {
        address = Address();
        town = "";
    }
}

bool Package::putPackage(const std::string &package) {
    if(weight != float(0))
        return false;
    std::istringstream input{package};
    std::string line;
    float inputNumber;

    getline(input,line);
    std::istringstream inputNumberStream{line};
    if(inputNumberStream >> inputNumber && inputNumber > 0)
    {
        getline(input,line);
        try{address.putAddress(line);}
        catch(WrongInput e){
            return false;
        }
        weight = inputNumber;
        std::string postalCode = address.getAddress().substr(0,5);
        setTown(postalCode);
        return true;

    }
    return false;


}
void Package::setTown(const std::string &postalCode)
{
    // podla 2 najvacsich cislic vypocita kde pojde zasielka
    std::multiset<int> digits;
    for (char i : postalCode)
        digits.insert(int(i-'0'));
    auto iter = digits.end();
    int first = *std::prev(iter);
    int second = *std::prev(std::prev(iter));
    town = mapOfTowns.at((first+second)%12);

}

bool Package::operator <(const Package &other)const {
    return weight < other.weight;
}

bool Package::operator >(const Package &other)const {
    return weight > other.weight;
}