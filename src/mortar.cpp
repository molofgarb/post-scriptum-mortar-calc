#include "mortar.h"

#include <iostream>
#include <string>

using std::endl;

Mortar::Mortar(const std::string& grid, const std::string& name,
               int type, DistToMils* table):
        Coordinate(grid), name(name), type(type), conversion_table(table) {}

double Mortar::milradians(const Coordinate& target) const {
    return conversion_table->convert(distance(target), type);
}

std::ostream& operator<<(std::ostream& os, const Mortar& rhs) {
    return rhs.display(os);
}

std::ostream& Mortar::display(std::ostream& os) const {
    os << name << ": "; 
    Coordinate::display(os);
    return os;
}