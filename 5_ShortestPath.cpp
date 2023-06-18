#include "4_ShippingArea.h"

std::pair<std::string,int> ShippingArea::minimumCostPath(const std::string &town1,const std::string &town2) const{
    std::vector<std::string> finalPath;
    std::set<std::string> visited;
    std::vector<std::string> path;
    std::string output;
    int distance = 10000;
    minimumPathRecursion(town1,town2,visited,
                         path,finalPath,0,distance);
    for(auto iter = finalPath.begin(); iter != finalPath.end(); iter++)
    {
        output += *iter;
        if (iter != std::prev(finalPath.end()))
            output += ",";
    }
    std::pair<std::string,int> result;
    result.first = output;
    result.second = distance;

    return result;

}
void ShippingArea:: minimumPathRecursion (const std::string &currentTown,const std::string &finalTown,std::set<std::string>&visited,
                                          std::vector<std::string>&path,std::vector<std::string>&finalPath,const int &currentDistance ,
                                          int &shortestDistance) const{
    path.push_back(currentTown);
    std::set<std::string> towns1 = townsToVisit();
    if (currentTown == finalTown)
    {
        if (isSubset(towns1,path) && currentDistance < shortestDistance)
        {
            finalPath = path;
            shortestDistance = currentDistance;
        }
    }
    else{
        auto it = visited.insert(currentTown);
        auto neighbours = getMapOfneighbours(currentTown);
        for(auto &elem : neighbours)
        {
            if (visited.find(elem.first) == visited.end())

                minimumPathRecursion(elem.first,finalTown,visited,path,finalPath,
                                     currentDistance + getDistance(currentTown,elem.first),
                                     shortestDistance );
        }
        visited.erase(it.first);
    }
    path.pop_back();
}
std::pair<int,std::string> ShippingArea:: courierMinimumCostPath() const{
    std::set<std::string> shippingTowns = townsToVisit();
    shippingTowns.erase(courier.getLocation());
    std::set<std::pair<int,std::string>> possiblePaths;

    for (auto &elem : shippingTowns ) {
        auto endingElement = minimumCostPath(courier.getLocation(), elem);
        std::pair<int, std::string> current;
        current.first = endingElement.second;
        current.second = endingElement.first;
        possiblePaths.insert(current);
    }
    return *possiblePaths.begin();
}