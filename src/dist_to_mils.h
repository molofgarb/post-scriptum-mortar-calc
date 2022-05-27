#ifndef DIST_TO_MILS_H
#define DIST_TO_MILS_H

#include <fstream>
#include <utility>
#include <map>

#define MAX_SHORT_DIST 1400
#define MAX_LONG_DIST 2500
#define SHORT_INTERVAL 50
#define LONG_INTERVAL 100

class DistToMils {
public:
    DistToMils(std::istream& is);

    double operator()(double distance, bool shortMortar) const;
private:
    double convertShort(int distance) const;
    double convertLong(int distance) const;

    std::map<int, std::pair<int, int>> table; //conversions
};

#endif