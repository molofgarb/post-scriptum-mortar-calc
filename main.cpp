#include "coordinate.h"
using std::cin;
using std::cout;
using std::endl;

int main() {
    bool brit4cm;
    std::string mortarLoc, targetLoc;
    cout << "Post Scriptum Mortar Calculator\n"
        "When inputting coordinates, additional numpads can be added for accuracy\n"
        "(ex. A1-7-7-7-7-...)\n"
        "To exit at any time, type \"exit\" as an input\n" << endl;
    while (true) {
        Coordinate mortar(mortarLoc), target(targetLoc);

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

        
        cout << "Distance: " << mortar.distance(target) << " m" << endl;
        cout << "Angle: " << mortar.angle(target) << " degrees" << endl;
        cout << endl;
    }
    cout << "An error has occurred..."
    "(press enter to quit)" << endl;
    std::getchar();
}