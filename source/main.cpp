#include <iostream>
#include "mouseMover.h"

using namespace mm;
using namespace std;

int main() {
    srand((unsigned)time(0));
    cout << "Starting bot!" << endl;
    mouseMover mouse;
    mouse.bezier(800, 500, 4, 500);
    return 0;
}