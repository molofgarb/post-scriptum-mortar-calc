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

void cli(); //command line interface with program
Mortar setMortar(const std::vector<std::string>& names, const DistToMils& table);
inline void getline(std::istream& is, std::string& str);

int main() {
    cli();
}

void cli() {
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
    while (true) {
        std::string input;
        Mortar mortar("", nullptr);
        Coordinate target("");

        //begin program
        cout << "\n\nPost Scriptum Mortar Calculator\n"
        "When inputting coordinates, additional numpads can be added for accuracy\n"
        "(ex. A1-7-7-7-7-...)\n"
        "To exit at any time, type \"exit\" as an input or press Ctrl+C\n"
        "To set a new mortar, type \"new\"" << "\n\n";

        while (true) { //try to create a mortar
            mortar = setMortar(mortarNames, table);
            if (mortar.validMortar()) {
                break;
            } else {
                cout << "Invalid mortar coordinate, please try again" << endl;
            }
        }

        while (true) {
            //get target coordinate info
            cout << "Please enter target location below: (ex. A1-7-7)" << '\n';
            getline(cin, input);
            cout << endl;
            if (input == "new") { //set new mortar location
                mortar = setMortar(mortarNames, table);
                if (!mortar.validMortar()) {
                    std::cerr << "Invalid mortar coordinate, restarting program";
                    break;
                }
            } else { //take target and perform calculations
                std::replace(input.begin(), input.end(), ' ', '-');

                //try to create a target
                try {
                    target = Coordinate(input); }
                catch (...) {
                    std::cerr << "Invalid target coordinate, restarting program";
                    break;
                }

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
        return Mortar("", nullptr);
    }
    cout << endl;

    //get mortar type info
    while (true) {
        cout << "Please enter mortar type: 1 for British 4cm mortar, 0 for all other mortars" << '\n';
        getline(cin, input);
        cout << endl;

        //try to modify mortar using the type specified
        try {
            int inputInt = std::stoi(input);
            if (inputInt < 0 || inputInt > 1) {
                throw std::invalid_argument("invalid mortar type");
            } else {
                mortar.setType(inputInt);
                return mortar;
            }
        }
        catch (...) {
            cout << "Invalid mortar type, please enter a valid type" << '\n';
            cout << endl;
        }
    }
}

inline void getline(std::istream& is, std::string& str) {
    std::getline(is, str);
    if (str == "exit") 
        exit(0);
}