#ifndef CUBE_H
#define CUBE_H

#include <Side.h>
#define NUM_OF_SIDES 6

class Cube : Side {
private:
    std::array<Side, NUM_OF_SIDES> sides {};
    Side* up {};
    Side* left {};
    Side* front {};
    Side* back {};
    Side* right {};
    Side* down {};

    void initailizeCube();

    std::string colorsToString(Colors color);
    void makeTurn(const std::array<Side*, 4>& relevant_sides, const std::array<int, 3>& left_side_squares);
    void rotateHelper(const std::array<Side*, 4>& relevant_sides);
    void rotate_side_counterclockwise(Side* side);
    void rotate_side_clockwise(Side* side);

public:

   Cube();

    Side& getSide(Colors color);

    void printCube();

    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();

    void left_up();
    void left_down();
    void right_up();
    void right_down();
    void middle_up();
    void middle_down();
    void top_left();
    void top_right();
    void bottom_left();
    void bottom_right();
    void front_right();
    //void front_left();
    //void back_right();
    //void back_left();
    //void middle_left();
    //void middle_right();

    void swap();
    void test();
};

#endif
