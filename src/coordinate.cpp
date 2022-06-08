#include "coordinate.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

const int kScale = 300;
const double kPi = 2 * acos(0.0);

// ============ SubCoordinate ============

//stores numpad coordinate relative to top-left corner as bounded xy
Coordinate::SubCoordinate::SubCoordinate(const std::vector<int>& numpads) {
    std::pair<int, int> coord = numpadToSubCoord(numpads,
        std::pow(3, numpads.size() - 1));
    x = coord.first;
    y = coord.second;
    size = std::pow(3, numpads.size());
}

//converts numpad coordinate relative to top-left corner to xy coordinate
std::pair<int, int> Coordinate::SubCoordinate::numpadToSubCoord(const std::vector<int>& numpads, 
                                                                int mult) {
    std::pair<int, int> coord = std::make_pair(0, 0);
    for (size_t i = 0; i < numpads.size(); i++) {
        coord.first += ((numpads[i] - 1) % 3) * mult;
        coord.second += (2 - ((numpads[i] - 1) / 3)) * (mult);
        mult /= 3;
    }
    return coord;
}

//returns coordinates as a ratio of distance to max distance
inline double Coordinate::SubCoordinate::xToDouble() const { 
    return (double) x / (double) size; 
}
inline double Coordinate::SubCoordinate::yToDouble() const { 
    return (double) y / (double) size; 
}

//returns stored data
inline int Coordinate::SubCoordinate::getX() const {
    return x; }
inline int Coordinate::SubCoordinate::getY() const {
    return y; }
inline int Coordinate::SubCoordinate::getSize() const {
    return size; }

//converts bounded xy coordinate back to 
std::ostream& operator<<(std::ostream& os, const Coordinate::SubCoordinate& rhs) {
    int x = rhs.getX();
    int y = rhs.getY();
    int size = rhs.getSize();
    std::vector<int> numpads; 
    while (size > 1) { //generate numpad coordinates
        int xDist = x / (size / 3); //highest-level distance from origin 
        int yDist = y / (size / 3);
        numpads.push_back( //convert dist (0,1,2) units to numpad
            (7 - (yDist * 3)) + xDist
        );
        size /= 3; 
        x %= size; //remove all solid grids and keep remainder
        y %= size;
    }
    for (auto i = 0; i < numpads.size(); ++i)
        os << numpads[i] << ((i == numpads.size() - 1) ? "" : "-");
    return os;
}

// ============ Coordinate ============

//parses coordinate string
Coordinate::Coordinate(const std::string& grid):
        x(-1), y(-1), sc(nullptr) {
    std::stringstream gridStream(grid);

    char xChar;
    gridStream >> xChar;
    x = std::toupper(xChar) - 'A';

    gridStream >> y;
    --y;

    std::vector<int> numpads;
    for (size_t i = 3; i < grid.size(); i += 2)
        numpads.push_back(grid[i] - '0');
    sc = new SubCoordinate(numpads);
}

Coordinate::Coordinate(const Coordinate& other):
    x(other.x), y(other.y) {
    sc = new SubCoordinate(*other.sc);
}

Coordinate::~Coordinate() {
    delete sc;
}

Coordinate& Coordinate::operator=(const Coordinate& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        delete sc;
        sc = new SubCoordinate(*other.sc);
    }
    return *this;
}

//finds the x-component of vector between this and target
inline double Coordinate::xDiff(const Coordinate& target) const {
    return ((target.x + target.sc->xToDouble()) - (x + sc->xToDouble())) * kScale;
}

//finds the y-component of vector between this and target
inline double Coordinate::yDiff(const Coordinate& target) const {
    return ((target.y + target.sc->yToDouble()) - (y + sc->yToDouble())) * kScale;
}

double Coordinate::distance(const Coordinate& target) const {
    return std::sqrt(std::pow(xDiff(target), 2) + std::pow(yDiff(target), 2));
}

double Coordinate::angle(const Coordinate& target) const {
    double angleOut = (std::atan2(yDiff(target), xDiff(target)) * (180.0/kPi)) + 90.0;
    return (angleOut > 0) ? angleOut : 360.0 - angleOut;
}

std::ostream& Coordinate::display(std::ostream& os) const {
    os << (char)((char)x + 'A') << y + 1; //output xy
    os << '-' << *sc; //output numpad
    return os;
}

std::ostream& operator<<(std::ostream& os, const Coordinate& rhs) {
    return rhs.display(os);
}
