#include <iostream>
#pragma once
#include "1_Address.h"
#include <vector>
#include <set>
#include <map>

const std::vector<std::string> vectorOfTowns = {
        "TRNAVA","TRENCIN","TRSTENA","TVRDOSIN",
        "BRATISLAVA","ZVOLEN","POPRAD","NITRA",
        "LEOPOLDOV","ZILINA","MARTIN","KOSICE",
};
const std::map<int,std::string> mapOfTowns = {
        { 1, "TRENCIN" }, { 2, "TRSTENA" }, { 3, "TVRDOSIN" },{ 4, "BRATISLAVA" },
        { 5, "ZVOLEN" } , { 6, "POPRAD" },{ 7, "NITRA" },{ 8, "LEOPOLDOV" },
        { 9, "ZILINA" },{ 10, "MARTIN" },{ 10, "MARTIN" },{ 11, "KOSICE"},{ 0, "TRNAVA" }
};

//2.uloha
class Package {
  float weight = 0.0;
  Address address;
  std::string town;
 public:
    Package(const std::string &package);
    bool putPackage(const std::string &package ) ;
    void setTown(const std::string &postalCode);

    bool operator < (const Package &other)const;
    bool operator > (const Package &other)const;
    std::string getShippingAddress()const {return address.getAddress();};
    float getWeight()const  {return weight;}
    std::string getTown()const {return town;}

};

