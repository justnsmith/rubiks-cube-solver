#ifndef CUBE_H
#define CUBE_H

#include <Side.h>
#define NUM_OF_SIDES 6

class Cube : Side {
private:
    std::array<Side, NUM_OF_SIDES> sides;
    Side* up {};
    Side* down {};
    Side* left {};
    Side* front {};
    Side* right {};
    Side* back {};

    void initailizeCube();

    std::string colorsToString(Colors color);

   public:

   Cube();

    Side& getSide(Colors color);

    void printCube();

    void left_up();

    void swap();
};

#endif
