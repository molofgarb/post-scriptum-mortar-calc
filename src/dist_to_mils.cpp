#include "dist_to_mils.h"
#include <fstream>
#include <utility>
#include <map>

#include <string>
#include <cmath>

const int max_short_dist = 1400;
const int max_long_dist = 2500;
const int short_interval = 50;
const int long_interval = 100;

DistToMils::DistToMils(std::istream& is) {
    int range, shortMortar, longMortar;
    char comma;
    while (is >> range >> comma >> shortMortar >> comma >> longMortar) {
        table[range] = std::make_pair(shortMortar, longMortar);
    }
}

double DistToMils::operator()(double distance, bool shortMortar) const {
    int roundedDist = (int)std::round(distance);
    if (shortMortar && roundedDist <= max_short_dist) //within bounds
        if (roundedDist % short_interval == 0) //on given mil
            return table.at(roundedDist).first;
        else //approx mil
            return convertShort(distance);
    else if (!shortMortar && distance <= max_long_dist) //within bounds
        if (roundedDist % long_interval == 0) //on given mil
            return table.at(roundedDist).second;
        else //approx mil
            return convertLong(distance);
    else
        return 0;
}

//Newton's method on interval between 
double DistToMils::convertShort(int distance) const {
    int upper = distance + (short_interval  - (distance % short_interval));
    int lower = distance - (distance % short_interval);
    double slope = (table.at(upper).first - table.at(lower).first)  
        / short_interval;
    return lower + (slope * (distance - lower));
}

double DistToMils::convertLong(int distance) const {
    int upper = distance + (long_interval  - (distance % long_interval));
    int lower = distance - (distance % long_interval);
    double slope = (table.at(upper).second - table.at(lower).second) 
        / long_interval;
    return lower + (slope * (distance - lower));
}