#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class Coordinate {
    //holds the portion of the coordinate described with numpad notation
    class SubCoordinate {
        friend std::ostream& operator<<(std::ostream& os, const SubCoordinate& rhs);
    public:
        SubCoordinate(const std::vector<int>& numpads);
        SubCoordinate(int x, int y, int size);
        double xToDouble() const;
        double yToDouble() const;

        inline int getX() const;
        inline int getY() const;
    private:
        std::pair<int, int> numpadToSubCoord(const std::vector<int>& numpads, int mult);

        int x; //distance from topleft in x
        int y; //distance from topleft in y
        int size; //total extent of distance
    };
public:
    Coordinate(const std::string& grid);
    Coordinate(const Coordinate& other);
    Coordinate& operator=(const Coordinate& other);
    
    ~Coordinate();
    
    double distance(const Coordinate& target) const; //distance between two coordinates
    double angle(const Coordinate& target) const;

private:
    friend std::ostream& operator<<(std::ostream& os, const Coordinate& rhs);

    //finds components of distance between two coordinates
    double xDiff(const Coordinate& target) const;
    double yDiff(const Coordinate& target) const;

    int x;
    int y;
    SubCoordinate* sc;
};

#endif