#ifndef CUBE_H
#define CUBE_H

#include <Side.h>
#define NUM_OF_SIDES 6

class Cube : Side {
private:
    std::array<Side, NUM_OF_SIDES> sides {};
    std::array<Side*, NUM_OF_SIDES> cube_side_order {};
    Side*& up = cube_side_order[0];
    Side*& left = cube_side_order[1];
    Side*& front = cube_side_order[2];
    Side*& right = cube_side_order[3];
    Side*& back = cube_side_order[4];
    Side*& down = cube_side_order[5];

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
