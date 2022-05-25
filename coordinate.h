#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class Coordinate {
public:
    Coordinate(const std::string& grid, bool mortar = true);
    Coordinate(const Coordinate& other);
    ~Coordinate();
    Coordinate& operator=(const Coordinate& other);

    double distance(const Coordinate& target) const; //distance between two coordinates

private:
    struct SubCoordinate {
        SubCoordinate(const std::vector<int>& numpads);
        SubCoordinate(int x, int y, int size);
        double xToDouble() const;
        double yToDouble() const;
        int x; //distance from topleft in x
        int y; //distance from topleft in y
        int size; //total extent of distance
    private:
        std::pair<int, int> numpadToSubCoord(const std::vector<int>& numpads, int mult);
    };

    double Coordinate::xDiff(const Coordinate& target) const;
    double Coordinate::yDiff(const Coordinate& target) const;

    int x;
    int y;
    SubCoordinate* sc;
    bool mortar; //mortar or target?
};

#endif