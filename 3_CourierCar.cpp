#include <sstream>
#include <vector>
#include "algorithm"
#include "2_Package.h"
#include "3_CourierCar.h"

//3.uloha
bool CourierCar::putPackage(const std::string &package) {
    Package newPackage = Package("");
    bool validPackage = newPackage.putPackage(package);
    if (!validPackage)
        return false;

    std::string country = newPackage.getShippingAddress();
    country = country.substr(6,country.size());
    if (weightOfAllPackages+newPackage.getWeight() <= maxWeight && country == "SLOVAKIA" )
    {
        packages.push_back(newPackage);
        numberOfPackages++;
        weightOfAllPackages += newPackage.getWeight();
        return true;
    }
    return false;
}


int CourierCar::putPackages(const std::string &packages) {
    std::string mypackages = packages + "\n\n";

    std::istringstream input{mypackages };
    std::string line;
    std::string output = "";
    int counterOfSucessfulInsertion = 0;

    while(std::getline(input,line))
    {
        if (line == "")
        {
            if(putPackage(output))
                counterOfSucessfulInsertion++;
            output = "";
        }
        else
        {
            output += line + '\n';
        }
    }
    return counterOfSucessfulInsertion;
}
Package &CourierCar::operator[](int index) {
    try {
        return packages.at(index);
    }
    catch (std::out_of_range) {
        Package *emptyPackage = new Package("");
        return *emptyPackage;
    }

}

void CourierCar::sortPackages()  {
    std::sort(packages.begin(),packages.end());

}
