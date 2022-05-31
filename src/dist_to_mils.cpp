#include "dist_to_mils.h"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>



//converts milradian data in a csv file 
DistToMils::DistToMils(std::istream& is, int mortarNum,
                       std::vector<int> maxDist, std::vector<int> interval):
         maxDist(maxDist), interval(interval) {
    char comma;
    std::string line;
    while (std::getline(is, line)) { //for every line in csv
        std::vector<int> mortars;
        int range = 0;
        std::string token;
        std::stringstream line_stream(line);
        while (std::getline(line_stream, token, ',')) { //break line into tokens
            if (range == 0) { //store range
                range = std::stoi(token);
            } else if (token != "") { //store milradian conversions
                mortars.push_back(std::stoi(token));
            } else { //no milradian value
                mortars.push_back(0);
            }
        }
        while (mortars.size() < mortarNum) //fill rest with unknown val
            mortars.push_back(0);
        table[range] = mortars;
    }
}

//converts a distance to milradian for specified mortar
double DistToMils::convert(double distance, int mortarType) const {
    int roundedDist = std::round(distance);
    if (roundedDist <= maxDist[mortarType]) //within bounds
        if (roundedDist % interval[mortarType] == 0) //on given mil
            return table.at(roundedDist)[mortarType];
        else //approx mil
            return approx(distance, mortarType);
    else
        return 0;
}

//Newton's method on interval between 
double DistToMils::approx(int distance, int mortarType) const {
    int inter = interval[mortarType];
    int upper = distance + (inter - (distance % inter)); //upper bound
    int lower = distance - (distance % inter); //lower bound
    double slope = (double)(table.at(upper)[mortarType] - table.at(lower)[mortarType]) / inter;
    return table.at(lower)[mortarType] + (slope * (distance - lower));
}

//output function (mostly used for debug)
std::ostream& operator<<(std::ostream& os, const DistToMils& rhs) {
    for (auto& i : rhs.table) {
        os << i.first << ": ";
        for (size_t j = 0; j < i.second.size(); ++j) {
            os << i.second[j] << ", ";
        }
        os << std::endl;
    } 
    return os << std::endl;
}