#include <Side.h>
#include <iostream>

Side::Colors& Side::getSquare(int index) {
    return squares[index];
}
