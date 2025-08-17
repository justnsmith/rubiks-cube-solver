#ifndef SIDE_H
#define SIDE_H

#include <array>
#define NUM_OF_SQUARES 9

class Side {
protected:
    enum Colors {
        Yellow,
        White,
        Blue,
        Red,
        Green,
        Orange
    };

    enum SquarePosition {
        TopLeftCorner,
        TopEdge,
        TopRightCorner,
        LeftEdge,
        Middle,
        RightEdge,
        BottomLeftCorner,
        BottomEdge,
        BottomRightCorner
    };

   std::array<Colors, NUM_OF_SQUARES> squares;

public:
    void printSide();
    Colors& getSquare(SquarePosition index);
};

#endif
