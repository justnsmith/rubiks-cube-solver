#ifndef CUBE_H
#define CUBE_H

#include <Side.h>
#define NUM_OF_SIDES 6

class Cube : Side {
private:
    std::array<Side, NUM_OF_SIDES> sides;

    void initailizeCube();

   public:

   Cube();

    Side& getSide(Colors color);

    void printCube();
};

#endif
