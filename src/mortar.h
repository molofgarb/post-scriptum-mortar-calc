#ifndef MORTAR_H
#define MORTAR_H

#include <iostream>
#include <string>

#include "coordinate.h"
#include "dist_to_mils.h"

class Mortar: public Coordinate {
public:
    Mortar(const std::string& grid, const std::string& name = "",
           int type = 0, DistToMils* table = nullptr);

    double milradians(const Coordinate& target) const;
protected:
    std::ostream& display(std::ostream& os) const;
private:
    friend std::ostream& operator<<(std::ostream& os, const Mortar& rhs);
    
    std::string name;
    int type;
    DistToMils* conversion_table;
};

#endif