#include <fstream>
#include <iostream>
#include "3_CourierCar.h"

bool CourierCar::readFromFile(const std::string &filename){
    std::ifstream inFile(filename);
    if (!inFile || !packages.empty()) {
        return false;
    }
    std::string onePackage;
    std::string line;
    while(std::getline(inFile,line))
    {
        if (line == "")
        {
            onePackage += "\n";
            putPackage(onePackage);
            onePackage = "";
        }

        else
            onePackage += line + "\n";
    }
    return true;

}
bool CourierCar::saveToFile(const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile || packages.empty())
        return false;
    for (size_t i = 0; i < numberOfPackages;i++ )
    {
        Package currentPackage = operator[](i);
        outfile << std::to_string(currentPackage.getWeight()) << "\n";
        outfile << currentPackage.getShippingAddress() <<"\n\n" ;
    }
    return true;
}