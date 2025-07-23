#include <Cube.h>
#include <iostream>
#include <cmath>

Cube::Cube() {
    initailizeCube();
}

void Cube::initailizeCube() {
  for (int side = 0; side < NUM_OF_SIDES; side++) {
    for (int square = 0; square < NUM_OF_SQUARES; square++) {
        sides[side].getSquare(square) = static_cast<Colors> (side);
    }
  }
}

void Cube::printCube() {
    std::cout << '\n';
    for (int side = 0; side < NUM_OF_SIDES; side++) {
        for (int square = 0; square < NUM_OF_SQUARES; square++) {
            std::cout << sides[side].getSquare(square);

            if (square % static_cast<int>(sqrt(NUM_OF_SQUARES)) == static_cast<int>(sqrt(NUM_OF_SQUARES)) - 1) {
                std::cout << '\n';
            }
        }
        if (side != NUM_OF_SIDES-1) {
            std::cout << '\n';
        }
    }
}

Cube::Side& Cube::getSide(Colors color) {
    return sides[color];
}
