#ifndef DIST_TO_MILS_H
#define DIST_TO_MILS_H

#include <fstream>
#include <map>
#include <vector>

class DistToMils {
public:
    DistToMils(std::istream& is, int mortarNum, std::vector<int> maxDist, std::vector<int> interval);

    double operator()(double distance, int mortarType) const;
private:
    double approx(int distance, int mortarType) const;

    friend std::ostream& operator<<(std::ostream& os, const DistToMils& rhs);

    std::map<int, std::vector<int>> table; //conversions - range, array of conversions
    std::vector<int> interval;
    std::vector<int> maxDist;
};

#endif