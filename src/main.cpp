#include <iostream>
#include <Cube.h>

using namespace std;

int main() {
    Cube cube;
    cube.printCube();
    cube.scramble();
    cube.printCube();
    cube.solve();
    cube.printCube();
}
