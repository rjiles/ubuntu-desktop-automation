#include <iostream>
#include "mouseMover.h"

using namespace mm;

int main() {
    std::cout << "Starting bot!";
    mouseMover mouse;
    mouse.move_mouse();
    return 0;
}