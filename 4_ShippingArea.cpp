#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>
#include "4_ShippingArea.h"

//4.uloha
void CourierCar::setLocationOfCar(const std::string &location1) {
  if (std::find(vectorOfTowns.begin(), vectorOfTowns.end(),location1) != vectorOfTowns.end())
      location = location1;
}

ShippingArea::ShippingArea(const std::string &filename,const CourierCar &courier1): courier(courier1){
   CourierCar emptyCourier;
    if (!makeGraphFromFile(filename))
        courier = emptyCourier;

}
bool ShippingArea::makeGraphFromFile(const std::string &filename){
    std::ifstream inFile(filename);
    if (!inFile)
        return false;
    std::string line,town1,town2;
    int distance;
    while(std::getline(inFile,line))
    {
        std::istringstream line1(line);
        line1 >> town1 >> town2 >> distance;


        std::map<std::string,int>neighboursOfTown1 = getMapOfneighbours(town1);
        std::map<std::string,int>neighboursOfTown2 = getMapOfneighbours(town2);
        if (neighboursOfTown1.empty())
        {
            neighboursOfTown1.insert(std::pair<std::string,int>(town2,distance));
            graphOfArea.insert(std::pair<std::string,std::map<std::string,int>>(town1,neighboursOfTown1));
        }else
        {
            neighboursOfTown1.insert(std::pair<std::string,int>(town2,distance));
            graphOfArea[town1] = neighboursOfTown1;
        }
        if (neighboursOfTown2.empty())
        {
            neighboursOfTown2.insert(std::pair<std::string,int>(town1,distance));
            graphOfArea.insert(std::pair<std::string,std::map<std::string,int>>(town2,neighboursOfTown2));
        }else
        {
            neighboursOfTown2.insert(std::pair<std::string,int>(town1,distance));
            graphOfArea[town2] = neighboursOfTown2;
        }
    }
    return true;
}

std::string ShippingArea::getNeighbours(const std::string &town1)const{
    std::string output = "";
    std::map<std::string,int> neighbours = getMapOfneighbours(town1);
    for(auto iter = neighbours.begin();iter != neighbours.end();++iter)
    {
        output += iter->first;
        if (iter != std::prev(neighbours.end()))
            output += ",";
    }
    return output;
}

int ShippingArea::getDistance(const std::string &town1,const std::string &town2)const{
    if(town1 == town2)
        return 0;
    std::map<std::string,int> neighbours = getMapOfneighbours(town1);
    try {
        return neighbours.at(town2);
    }
    catch (std::out_of_range) {
        return 0;
    }

};
std::map<std::string,int> ShippingArea::getMapOfneighbours(const std::string &town1)const{
    std::map<std::string,int> neighbours;
    try {
        neighbours = graphOfArea.at(town1);
    }
    catch (std::out_of_range) {}
    return neighbours;
}


std::set<std::string> ShippingArea::townsToVisit()const{
    std::set<std::string> towns;
    CourierCar newCourier = courier;
    for (size_t i = 0;i < courier.getNumberOfpackages();++i )
    {
        towns.insert(newCourier[i].getTown());
    }
    return towns;
}

bool ShippingArea::isSubset(std::set<std::string> &container1,std::vector<std::string> &container2) const{
    for (auto &elem : container1)
    {
        if (std::find(container2.begin(),container2.end(),elem) == container2.end())
            return false;
    }
    return true;
}

std::string ShippingArea::findPossiblePathForCourier()const{
    std::string output;
    std::set<std::string> visitedTowns;
    std::set<std::string> shippingTowns = townsToVisit();
    std::vector<std::string> path;
    std::vector<std::string> resultPath;
    backtracking(courier.getLocation(),
                 visitedTowns,
                 path,shippingTowns,
                 resultPath);
    for(auto iter = resultPath.begin(); iter != resultPath.end(); iter++)
    {
        output += *iter;
        if (iter != std::prev(resultPath.end()))
            output += ",";
    }
    return output;

}

void ShippingArea::backtracking(std::string currentTown,std::set<std::string>&visited,std::vector<std::string> &path,
                                std::set<std::string>&shippingTowns,std::vector<std::string> &resultPath)const{
    path.push_back(currentTown);
    if(isSubset(shippingTowns,path))
        resultPath = path;
    else
    {
        auto it = visited.insert(currentTown);
        auto neighbours = getMapOfneighbours(currentTown);
        for(auto iter = neighbours.begin();iter != neighbours.end();++iter)
        {
            std::string possibleNeighbour = iter->first;
            if(visited.find(possibleNeighbour) == visited.end())
                backtracking(possibleNeighbour,visited,path,shippingTowns,resultPath);
        }
        visited.erase(it.first);
    }
    path.pop_back();

}


