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
        cout << "Please enter mortar location below: (ex. A1-7-7)" << endl;
        cin >> mortarLoc;
        if (mortarLoc == "exit") exit(0);

        cout << "Please enter target location below: (ex. A1-7-7)" << endl;
        cin >> targetLoc;
        if (targetLoc == "exit") exit(0);

        Coordinate mortar(mortarLoc), target(targetLoc);
        cout << "Distance: " << mortar.distance(target) << " m" << endl;
        cout << "Angle: " << mortar.angle(target) << " degrees" << endl;
        cout << endl;
    }
}