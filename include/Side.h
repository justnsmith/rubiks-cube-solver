#ifndef SIDE_H
#define SIDE_H

#include <array>
#define NUM_OF_SQUARES 9

class Side {
public:
    enum Colors {
        yellow,
        white,
        blue,
        red,
        green,
        orange
    };

   std::array<Colors, NUM_OF_SQUARES> squares;

public:
    void printSide();
    Colors& getSquare(int index);
};

#endif
