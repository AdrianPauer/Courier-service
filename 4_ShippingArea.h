#pragma once
#include "3_CourierCar.h"
#include <map>
#include <set>
#include <vector>
class  ShippingArea{
    std::map<std::string,std::map<std::string,int>> graphOfArea;
    CourierCar courier;
public:
    CourierCar getCourier() const { return courier; };

    ShippingArea(const std::string &filename,const CourierCar &courier1);
    bool makeGraphFromFile(const std::string &filename);

    std::string getNeighbours(const std::string &town1) const;
    int getDistance(const std::string &town1,const std::string &town2)const;
    std::set<std::string> townsToVisit()const;
    std::map<std::string,int> getMapOfneighbours(const std::string &town1)const;

    bool isSubset(std::set<std::string> &container1,std::vector<std::string> &container2) const;

    std::string findPossiblePathForCourier()const;
    void backtracking(std::string currentTown,std::set<std::string>&visited,std::vector<std::string> &path,
                      std::set<std::string>&shippingTowns,std::vector<std::string> &resultPath)const;

    // 5.uloha
    std::pair<std::string,int> minimumCostPath(const std::string &town1,const std::string &town2) const;
    void minimumPathRecursion(const std::string &currentTown,const std::string &finalTown,std::set<std::string>&visited,
                              std::vector<std::string>&path,std::vector<std::string>&finalPath,
                             const int &currentDistance,int &shortestDistance ) const;
    std::pair<int,std::string> courierMinimumCostPath() const;
};

