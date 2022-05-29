#include "coordinate.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "dist_to_mils.h"
#include <fstream>
#include <map>

#include <cmath>

using std::cin;
using std::cout;
using std::endl;


int main() {
    bool brit4cm; //this is temporary while mortar class is unimplemented
    std::string mortarLoc, targetLoc;
    Coordinate mortar(mortarLoc), target(targetLoc);

    //open conversion chart and initialize converter obj
    std::ifstream mil_table("PostScriptumMortarMils.csv");
    if (!mil_table) {
        std::cerr << "Unable to find file";
        exit(1);
    }
    std::vector<int> maxDist{1400, 2500};
    std::vector<int> interval{50, 100};
    DistToMils conversion(mil_table, 2, maxDist, interval);
    mil_table.close();

    //begin program
    cout << "Post Scriptum Mortar Calculator\n"
        "When inputting coordinates, additional numpads can be added for accuracy\n"
        "(ex. A1-7-7-7-7-...)\n"
        "To exit at any time, type \"exit\" as an input or press Ctrl+C\n" << endl;

    while (true) {
        cout << "Please enter mortar location below: (ex. A1-7-7)" << endl;
        cin >> mortarLoc;
        if (mortarLoc == "exit") exit(0);
        try {
            mortar = Coordinate(mortarLoc); }
        catch (...) {
            exit(1); }

        cout << "Please enter target location below: (ex. A1-7-7)" << endl;
        cin >> targetLoc;
        if (targetLoc == "exit") exit(0);
        try {
            target = Coordinate(targetLoc); }
        catch (...) {
            exit(1); }
        cout << endl;

        double distance = mortar.distance(target);
        cout << "Distance: " << distance << " m" << endl;
        cout << "Angle: " << mortar.angle(target) << " degrees" << endl;
<<<<<<< HEAD
        // cout << mortar << endl;
        // cout << target << endl;
        // cout << endl;
=======
        cout << "Milradians: " << conversion(distance, 0) << " milradians" << endl;
        cout << "\n";
        cout << "Mortar Coordinate: " << mortar << endl;
        cout << "Target Coordinate: " << target << endl;
        cout << "\n\n" << endl;
>>>>>>> coord-stringstr
    }

    cout << "An error has occurred..."
    "(press enter to quit)" << endl;
    std::getchar();
}