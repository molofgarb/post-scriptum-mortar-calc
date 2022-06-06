#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class Coordinate {
    //holds the portion of the coordinate described with numpad notation
    class SubCoordinate {
        
    public:
        SubCoordinate(const std::vector<int>& numpads);
        SubCoordinate(int x, int y, int size);
        inline double xToDouble() const;
        inline double yToDouble() const;

        inline int getX() const;
        inline int getY() const;
        inline int getSize() const;
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
    
    inline double distance(const Coordinate& target) const; //distance between two coordinates
    inline double angle(const Coordinate& target) const;

protected:
    virtual std::ostream& display(std::ostream& os) const;
private:
    //finds components of distance between two coordinates
    inline double xDiff(const Coordinate& target) const;
    inline double yDiff(const Coordinate& target) const;

    friend std::ostream& operator<<(std::ostream& os, const Coordinate& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Coordinate::SubCoordinate& rhs);

    int x;
    int y;
    SubCoordinate* sc;
};

#endif