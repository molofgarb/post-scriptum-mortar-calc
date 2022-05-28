#include "dist_to_mils.h"
#include <fstream>
#include <map>

#include <string>
#include <cmath>

const int kMaxShortDist = 1400;
const int kMaxLongDist = 2500;
const int kShortInterval = 50;
const int kLongInterval = 100;

DistToMils::Mils::Mils(int short_mortar, int long_mortar):
    short_mortar(short_mortar), long_mortar(long_mortar) {}

DistToMils::DistToMils(std::istream& is) {
    int range, shortMortar, longMortar;
    char comma;
    while (is >> range >> comma >> shortMortar >> comma >> longMortar) {
        table[range] = DistToMils::Mils(shortMortar, longMortar);
    }
}

double DistToMils::operator()(double distance, bool shortMortar) const {
    int roundedDist = (int)std::round(distance);
    if (shortMortar && roundedDist <= kMaxShortDist) //within bounds
        if (roundedDist % kShortInterval == 0) //on given mil
            return table.at(roundedDist).short_mortar;
        else //approx mil
            return convertShort(distance);
    else if (!shortMortar && distance <= kMaxLongDist) //within bounds
        if (roundedDist % kLongInterval == 0) //on given mil
            return table.at(roundedDist).long_mortar;
        else //approx mil
            return convertLong(distance);
    else
        return 0;
}

//Newton's method on interval between 
inline double DistToMils::convertShort(int distance) const {
    int upper = distance + (kShortInterval  - (distance % kShortInterval));
    int lower = distance - (distance % kShortInterval);
    double slope = (table.at(upper).short_mortar - table.at(lower).short_mortar)  
        / kShortInterval;
    return lower + (slope * (distance - lower));
}

inline double DistToMils::convertLong(int distance) const {
    int upper = distance + (kLongInterval  - (distance % kLongInterval));
    int lower = distance - (distance % kLongInterval);
    double slope = (table.at(upper).long_mortar - table.at(lower).long_mortar) 
        / kLongInterval;
    return lower + (slope * (distance - lower));
}