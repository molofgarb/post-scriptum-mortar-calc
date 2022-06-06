#include "mortar.h"

#include <iostream>
#include <string>
#include <vector>

using std::endl;

Mortar::Mortar(const std::string& grid, const std::vector<std::string>* names,
               const DistToMils* table, int type):
        Coordinate(grid), names(names), conversion_table(table), type(type) {}

double Mortar::milradians(const Coordinate& target) const {
    return conversion_table->convert(distance(target), type);
}

void Mortar::setType(int newType) {
    type = newType; }

bool Mortar::validMortar() const {
    return names != nullptr; }

std::ostream& operator<<(std::ostream& os, const Mortar& rhs) {
    return rhs.display(os);
}

std::ostream& Mortar::display(std::ostream& os) const {
    os << (*names)[type] << ": "; 
    Coordinate::display(os);
    return os;
}