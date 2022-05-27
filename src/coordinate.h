#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class Coordinate {
    friend std::ostream& operator<<(std::ostream& os, const Coordinate& rhs);
public:
    Coordinate(const std::string& grid);
    Coordinate(const Coordinate& other);
    ~Coordinate();
    Coordinate& operator=(const Coordinate& other);

    double distance(const Coordinate& target) const; //distance between two coordinates
    double angle(const Coordinate& target) const;

private:
    //holds the portion of the coordinate described with numpad notation
    struct SubCoordinate {
        SubCoordinate(const std::vector<int>& numpads);
        SubCoordinate(int x, int y, int size);
        double xToDouble() const;
        double yToDouble() const;
        int x; //distance from topleft in x
        int y; //distance from topleft in y
        int size; //total extent of distance
    private:
        friend std::ostream& operator<<(std::ostream& os, const SubCoordinate& rhs);
        std::pair<int, int> numpadToSubCoord(const std::vector<int>& numpads, int mult);
    };

    //finds components of distance between two coordinates
    double xDiff(const Coordinate& target) const;
    double yDiff(const Coordinate& target) const;

    int x;
    int y;
    SubCoordinate* sc;
};

#endif