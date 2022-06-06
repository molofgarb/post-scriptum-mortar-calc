#ifndef MORTAR_H
#define MORTAR_H

#include <iostream>
#include <string>
#include <vector>

#include "coordinate.h"
#include "dist_to_mils.h"

class Mortar: public Coordinate {
public:
    Mortar(const std::string& grid, const std::vector<std::string>* names,
           const DistToMils* table = nullptr, int type = -1);

    double milradians(const Coordinate& target) const;

    void setType(int newType);
    bool validMortar() const;
protected:
    std::ostream& display(std::ostream& os) const;
private:
    friend std::ostream& operator<<(std::ostream& os, const Mortar& rhs);
    
    const std::vector<std::string>* names;
    const DistToMils* conversion_table;
    int type;
};

#endif