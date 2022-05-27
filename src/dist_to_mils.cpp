#include "dist_to_mils.h"
#include <string>
#include <cmath>

DistToMils::DistToMils(std::istream& is) {
    int range, shortMortar, longMortar;
    char comma;
    while (is >> range >> comma >> shortMortar >> comma >> longMortar) {
        table[range] = std::make_pair(shortMortar, longMortar);
    }
}

double DistToMils::operator()(double distance, bool shortMortar) const {
    int roundedDist = (int)std::round(distance);
    if (shortMortar && roundedDist <= MAX_SHORT_DIST) //within bounds
        if (roundedDist % SHORT_INTERVAL == 0) //on given mil
            return table.at(roundedDist).first;
        else //approx mil
            return convertShort(distance);
    else if (!shortMortar && distance <= MAX_LONG_DIST) //within bounds
        if (roundedDist % LONG_INTERVAL == 0) //on given mil
            return table.at(roundedDist).second;
        else //approx mil
            return convertLong(distance);
    else
        return 0;
}

//Newton's method on interval between 
double DistToMils::convertShort(int distance) const {
    int upper = distance + (SHORT_INTERVAL  - (distance % SHORT_INTERVAL));
    int lower = distance - (distance % SHORT_INTERVAL);
    double slope = (table.at(upper).first - table.at(lower).first)  
        / SHORT_INTERVAL;
    return lower + (slope * (distance - lower));
}

double DistToMils::convertLong(int distance) const {
    int upper = distance + (LONG_INTERVAL  - (distance % LONG_INTERVAL));
    int lower = distance - (distance % LONG_INTERVAL);
    double slope = (table.at(upper).second - table.at(lower).second) 
        / LONG_INTERVAL;
    return lower + (slope * (distance - lower));
}