#include <iostream>
#include <Cube.h>

using namespace std;

int main() {
    Cube cube;
    cube.printCube();
    cube.middle_up();
    cube.printCube();
    cube.getSide(static_cast<Side::Colors>(Side::white)).printSide();
}
