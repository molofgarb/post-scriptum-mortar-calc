#ifndef DIST_TO_MILS_H
#define DIST_TO_MILS_H

#include <fstream>
#include <map>

class DistToMils {
    struct Mils {
        Mils(int short_mortar = 0, int long_mortar = 0);
        int short_mortar;
        int long_mortar;
    };
public:
    DistToMils(std::istream& is);

    double operator()(double distance, bool shortMortar) const;
private:
    double convertShort(int distance) const;
    double convertLong(int distance) const;

    std::map<int, Mils> table; //conversions
};

#endif