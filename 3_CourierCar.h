#pragma once
#include <vector>
#include "2_Package.h"
const int maxWeight = 2000;

class CourierCar {
    std::vector<Package> packages;
    int numberOfPackages = 0;
    double weightOfAllPackages = 0;
    std::string location = "BRATISLAVA";
public:
    void setLocationOfCar(const std::string &location1);
    bool putPackage(const std::string &package);
    int putPackages(const std::string &packages);
    int getNumberOfpackages() const { return numberOfPackages; };
    std::string getLocation() const {return location;};
    void sortPackages();
    bool readFromFile(const std::string &filename);
    bool saveToFile(const std::string &filename);
    Package &operator [] (int index) ;


};
