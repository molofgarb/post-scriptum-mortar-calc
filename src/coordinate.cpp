#include "coordinate.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <cmath>

using std::cin;
using std::cout;
using std::endl;

const int scale = 300;
const int pi = 2 * acos(0.0);

// ============ SubCoordinate ============

//converts numpad coordinate relative to top-left corner to xy coordinate
Coordinate::SubCoordinate::SubCoordinate(const std::vector<int>& numpads) {
    std::pair<int, int> coord = numpadToSubCoord(numpads,
        std::pow(3, numpads.size() - 1));
    x = coord.first;
    y = coord.second;
    size = std::pow(3, numpads.size());
}

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



// ============ Coordinate ============

Coordinate::Coordinate(const std::string& grid) {
    x = std::toupper(grid[0]) - 'A';
    y = (grid[2] == '-') ? grid[1] : (grid[1] * 10 + grid[2]);
    if (grid[2] == '-')
        cout << grid[1] << endl;
    else 
        cout << (grid[1] * 10) + (int)grid[2] << endl;
    std::vector<int> numpads;
    for (size_t i = 3; i < grid.size(); i += 2)
        numpads.push_back(grid[i]);
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
    return ((target.x + target.sc->xToDouble()) - (x + sc->xToDouble())) * scale;
}

//finds the y-component of vector between this and target
double Coordinate::yDiff(const Coordinate& target) const {
    return ((target.y + target.sc->yToDouble()) - (y + sc->yToDouble())) * scale;
}

double Coordinate::distance(const Coordinate& target) const {
    return std::sqrt(std::pow(xDiff(target), 2) + std::pow(yDiff(target), 2));
}

double Coordinate::angle(const Coordinate& target) const {
    return (std::atan2(yDiff(target), xDiff(target)) * (180/pi)) + 90.0;
}

std::ostream& operator<<(std::ostream& os, const Coordinate& rhs) {
    os << (char) (rhs.x + 'A') << rhs.y;
    int x = rhs.sc->x;
    int y = rhs.sc->y;
    // int mult = rhs.sc->size / 3;
    // while (x > 0) {
    //     os << '-' << (x + 1) + ((y + 1) * 3);
    //     x /= 3;
    //     y /= 3;
    // }
    return os;
}



// int main() {
//     // std::vector<int> numpads = {3, 4, 5};
//     // Coordinate::SubCoordinate test(numpads);
//     // std::cout << "x: " << test.x << std::endl;
//     // std::cout << "y: " << test.y << std::endl;
//     // std::cout << "size: " << test.size << std::endl;

//     cout << Coordinate("A1-7-7").distance(Coordinate("B1-7-7")) << endl; //300
//     cout << Coordinate("A1-7-7").distance(Coordinate("A2-7-7")) << endl; //300
//     cout << Coordinate("A1-7-7").distance(Coordinate("B2-7-7")) << endl; //300 * sqrt2 = 424
//     cout << Coordinate("A2-9-2").distance(Coordinate("D7-4-5")) << endl; //~1715
//     cout << endl;

//     cout << Coordinate("A1-7-7").angle(Coordinate("B1-7-7")) << endl; //90
//     cout << Coordinate("A1-7-7").angle(Coordinate("A2-7-7")) << endl; //180
//     cout << Coordinate("A1-7-7").angle(Coordinate("B2-7-7")) << endl; //135
//     cout << Coordinate("A2-9-2").angle(Coordinate("D7-4-5")) << endl; //somewhere in quadrant 2
//     std::cin.get();
// }