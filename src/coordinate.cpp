#include "coordinate.h"

#include <iostream>
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
double Coordinate::SubCoordinate::xToDouble() const { 
    return (double) x / (double) size; 
}
double Coordinate::SubCoordinate::yToDouble() const { 
    return (double) y / (double) size; 
}

//returns stored data
int Coordinate::SubCoordinate::getX() const {
    return x; }
int Coordinate::SubCoordinate::getY() const {
    return y; }
int Coordinate::SubCoordinate::getSize() const {
    return size; }

//converts bounded xy coordinate back to 
std::ostream& operator<<(std::ostream& os, const Coordinate::SubCoordinate& rhs) {
    int x = rhs.getX();
    int y = rhs.getY();
    int size = rhs.getSize();
    std::vector<int> numpads; //stored in reverse order - more to less detail
    while (size > 0) { //generate numpad coordinates
        numpads.push_back(
            (x % 3) + ((2 - (y % 3)) * 3) + 1
        );
        x /= 3;
        y /= 3;
        size /= 3;
    }
    for (int i = numpads.size() - 1; i > 0; --i)
        os << numpads[i] << ((i == 1) ? "" : "-");
    return os;
}

// ============ Coordinate ============

//parses coordinate string
Coordinate::Coordinate(const std::string& grid):
        x(-1), y(-1), sc(nullptr) {
    x = std::toupper(grid[0]) - 'A';
    y = (grid[2] == '-') ? 
        grid[1] - '1' : 
        ((grid[1] - '1') * 10 + (grid[2] - '1'));

    std::vector<int> numpads;
    for (size_t i = 3; i < grid.size(); i += 2)
        numpads.push_back(grid[i] - '0');
    sc = new SubCoordinate(numpads);
}

Coordinate::Coordinate(const Coordinate& other):
    x(x), y(y) {
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
double Coordinate::xDiff(const Coordinate& target) const {
    return ((target.x + target.sc->xToDouble()) - (x + sc->xToDouble())) * kScale;
}

//finds the y-component of vector between this and target
double Coordinate::yDiff(const Coordinate& target) const {
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
