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
    void inverse_move(Side* side, const std::array<int, 3>& original_squares, const std::array<int, 3>& new_squares);

public:

   Cube();

    Side& getSide(Colors color);

    void printCube();

    void rotate_up();    // WIP
    void rotate_down();  // WIP
    void rotate_left();  // WC
    void rotate_right(); // WC

    void left_up();      // WC
    void left_down();    // WC
    void right_up();     // WC
    void right_down();   // WC
    void middle_up();    // WC
    void middle_down();  // WC
    void middle_left();  // WC
    void middle_right(); // WC
    void top_left();     // WC
    void top_right();    // WC
    void bottom_left();  // WC
    void bottom_right(); // WC
    void front_right();  // WC
    void front_left();   // WC
    void back_right();   // WC
    void back_left();    // WC

    void swap();
    void test();
};

#endif
