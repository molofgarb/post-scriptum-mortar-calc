#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "coordinate.h"
#include "dist_to_mils.h"
#include "mortar.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
    //open conversion chart and initialize converter obj
    std::ifstream mil_table("PostScriptumMortarMils.csv");
    if (!mil_table) {
        std::cerr << "Unable to find file";
        exit(1);
    }
    std::vector<int> maxDist{1400, 2500};
    std::vector<int> interval{50, 100};
    DistToMils table(mil_table, 2, maxDist, interval);
    mil_table.close();

    std::vector<std::string> mortarNames{"Short Mortar", "Long Mortar"};
    std::string coord, type;
    Mortar mortar("");
    Coordinate target("");

    //begin program
    cout << "Post Scriptum Mortar Calculator\n"
        "When inputting coordinates, additional numpads can be added for accuracy\n"
        "(ex. A1-7-7-7-7-...)\n"
        "To exit at any time, type \"exit\" as an input or press Ctrl+C\n" << '\n';

    while (true) {
        //get mortar info
        cout << "Please enter mortar location below: (ex. A1-7-7)" << '\n';
        std::getline(cin, coord);
        if (coord == "exit") exit(0);
        std::replace(coord.begin(), coord.end(), ' ', '-');

        cout << "Please enter mortar type: 1 for British 4cm mortar, 0 for all other mortars" << '\n';
        std::getline(cin, type);
        if (type == "exit") exit(0);
        int intType = std::stoi(type);
        if (intType < 0 || intType > 1) {
            std::cerr << "Invalid mortar type, exiting program";
            exit(1);
        }

        try {
            mortar = Mortar(coord, mortarNames[intType], intType, &table); }
        catch (...) {
            std::cerr << "Invalid mortar coordinate, exiting program";
            exit(1);
        }
        cout << endl;

        //get target info
        cout << "Please enter target location below: (ex. A1-7-7)" << '\n';
        std::getline(cin, coord);
        if (coord == "exit") exit(0);
        std::replace(coord.begin(), coord.end(), ' ', '-');

        try {
            target = Coordinate(coord); }
        catch (...) {
            std::cerr << "Invalid target coordinate, exiting program";
            exit(1);
        }
        cout << endl;

        //results
        cout << "Mortar: " << mortar << '\n';
        cout << "Target: " << target << '\n';
        cout << "Distance: " << mortar.distance(target) << " m" << "\n\n";
        cout << endl;
        cout << "=====================" << '\n';
        cout << "Milradians: " << mortar.milradians(target) << " milradians" << '\n';
        cout << "Angle: " << mortar.angle(target) << " degrees" << '\n';
        cout << "=====================" << "\n\n";
        cout << endl;
    }
}