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

Mortar setMortar(const std::vector<std::string>& names, const DistToMils& table);
void getline(std::istream& is, std::string& str);

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

    bool skip;
    std::vector<std::string> mortarNames{"Short Mortar", "Long Mortar"};
    std::string input;
    Coordinate target("");

    //begin program
    cout << "\n\nPost Scriptum Mortar Calculator\n"
        "When inputting coordinates, additional numpads can be added for accuracy\n"
        "(ex. A1-7-7-7-7-...)\n"
        "To exit at any time, type \"exit\" as an input or press Ctrl+C\n"
        "To set a new mortar, type \"new\"" << "\n\n";
    
    Mortar mortar = setMortar(mortarNames, table);

    while (true) {
        //get target coordinate info
        cout << "Please enter target location below: (ex. A1-7-7)" << '\n';
        getline(cin, input);
        if (input == "new") { //set new mortar location
            cout << endl;
            mortar = setMortar(mortarNames, table);
        } else { //take target and perform calculations
            std::replace(input.begin(), input.end(), ' ', '-');

            //try to create a target
            try {
                target = Coordinate(input); }
            catch (...) {
                std::cerr << "Invalid target coordinate, exiting program";
                exit(1);
            }
            cout << endl;

            //calculate output
            double mils = mortar.milradians(target);
            cout << "Mortar: " << mortar << '\n';
            cout << "Target: " << target << '\n';
            cout << "Distance: " << mortar.distance(target) << " m" << "\n\n";
            cout << endl;
            cout << "===============================" << '\n';
            cout << "Milradians: ";
            if (mils == 0) {
                cout << "Out of range";
            } else {
                cout << mils << " milradians";
            }
            cout << '\n';
            cout << "Angle: " << mortar.angle(target) << " degrees" << '\n';
            cout << "===============================" << "\n\n";
            cout << endl;
        }
    }
}

Mortar setMortar(const std::vector<std::string>& names, const DistToMils& table) {
    std::string input;
    Mortar mortar("", &names);
    //get mortar coordinate info
    cout << "Please enter mortar location below: (ex. A1-7-7)" << '\n';
    getline(cin, input);
    
    std::replace(input.begin(), input.end(), ' ', '-');

    //try to create a mortar of default (short) type
    try {
        mortar = Mortar(input, &names, &table); }
    catch (...) {
        std::cerr << "Invalid mortar coordinate, exiting program";
        exit(1);
    }
    cout << endl;

    //get mortar type info
    cout << "Please enter mortar type: 1 for British 4cm mortar, 0 for all other mortars" << '\n';
    getline(cin, input);
    if (input == "exit")
        exit(0);

    //try to modify mortar using the type specified
    try {
        int inputInt = std::stoi(input);
        if (inputInt < 0 || inputInt > 1) {
            throw std::invalid_argument("Type not allowed");
        }
        mortar.setType(inputInt);
    }
    catch (...) {
        std::cerr << "Invalid mortar type, exiting program";
        exit(1);
    }
    cout << endl;
    return mortar;
}

void getline(std::istream& is, std::string& str) {
    std::getline(is, str);
    if (str == "exit") 
        exit(0);
}