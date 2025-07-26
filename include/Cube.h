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
    Side*& back = cube_side_order[3];
    Side*& right = cube_side_order[4];
    Side*& down = cube_side_order[5];

    void initailizeCube();

    std::string colorsToString(Colors color);
    void makeTurn(const std::array<Side*, 4>& relevant_sides, const std::array<int, 3>& left_side_squares);

public:

   Cube();

    Side& getSide(Colors color);

    void printCube();

    void left_up();
    void left_down();
    void right_up();
    void right_down();
    void middle_up();
    void middle_down();
    //void front_right();
    //void front_left();
    //void back_right();
    //void back_left();
    //void middle_left();
    //void middle_right();

    // SHOULD BE POSSIBLE WITHOUT TURNING WHOLE CUBE
    void top_left();
    void top_right();
    void bottom_left();
    void bottom_right();

    void swap();
};

#endif
