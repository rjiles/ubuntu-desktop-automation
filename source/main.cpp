#include <iostream>
#include "mouseMover.h"
#include "entityFinder.h"

using namespace mm;
using namespace ef;
using namespace std;

int main() {
    srand((unsigned)time(0));
    cout << "Starting bot!" << endl;
    mouseMover mouse;
    mouse.bezier(800, 500, 6, 1000);
    entityFinder finder;
    std::string test = "test";
    char* argv[2] = {"../entities/multi.png", "../entities/logo_2.png"};
    const int argc = sizeof(argv)/sizeof(char*);
    finder.find(argc, argv);
    return 0;
}