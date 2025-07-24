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

std::string Cube::colorsToString(Colors color) {
    switch (color) {
        case Colors::yellow: return "yellow";
        case Colors::white: return "white";
        case Colors::blue: return "blue";
        case Colors::red: return "red";
        case Colors::green: return "green";
        case Colors::orange: return "orange";
    }
}

// TEMPORARY CODE
void Cube::swap() {
    Side& first_side = getSide(white);
    Side& second_side = getSide(blue);
    const std::array<int, 3> left_side_squares = {0, 3, 6};
    Colors temp {};
    for (int i = 0; i < left_side_squares.size(); i++) {
        temp = first_side.getSquare(left_side_squares[i]);
        first_side.getSquare(left_side_squares[i]) = second_side.getSquare(left_side_squares[i]);
        second_side.getSquare(left_side_squares[i]) = temp;
    }
    printCube();
}

void Cube::left_up() {
    const std::array<Colors, 4> relevant_sides = {white, blue, yellow, green};
    const std::array<int, 3> left_side_squares = {0, 3, 6};
    Colors temp {};

    for (int i = 1; i < relevant_sides.size(); i++) {
        Side& currentSide = getSide(relevant_sides[i]);
        for (int j = 0; j < left_side_squares.size(); j++) {
            temp = getSide(relevant_sides[0]).getSquare(left_side_squares[j]);
            getSide(relevant_sides[0]).getSquare(left_side_squares[j]) = currentSide.getSquare(left_side_squares[j]);
            currentSide.getSquare(left_side_squares[j]) = temp;
        }
    }
}

