#include <Cube.h>
#include <iostream>
#include <cmath>

Cube::Cube() {
    initailizeCube();
}

void Cube::initailizeCube() {
    for (int side = 0; side < NUM_OF_SIDES; side++) {
        switch (static_cast<Colors> (side)) {
            case yellow:
                up = &sides[side];
                break;
            case white:
                down = &sides[side];
                break;
            case blue:
                left = &sides[side];
                break;
            case red:
                front = &sides[side];
                break;
            case green:
                right = &sides[side];
                break;
            case orange:
                back = &sides[side];
                break;
        }
        for (int square = 0; square < NUM_OF_SQUARES; square++) {
            sides[side].getSquare(square) = static_cast<Colors> (side);
        }
    }
}

void Cube::printCube() {
    const int num_of_body_sides = 4;
    const int row_of_squares = static_cast<int>(sqrt(NUM_OF_SQUARES));
    const int col_of_squares = static_cast<int>(sqrt(NUM_OF_SQUARES));
    std::cout << '\n';
    up->printSide();

    std::cout << "┌───┬───┬───┐ ┌───┬───┬───┐ ┌───┬───┬───┐ ┌───┬───┬───┐" << '\n';
    for (int i = 0; i < col_of_squares; i++) {
        for (int j = 0; j < row_of_squares * num_of_body_sides; j++) {
            std::cout << "│ ";

            switch (cube_side_order[(j / row_of_squares) + 1]->getSquare(j % row_of_squares)) {
                case yellow:
                    std::cout << "\033[93m";
                    break;
                case white:
                    std::cout << "\033[97m";
                    break;
                case blue:
                    std::cout << "\033[94m";
                    break;
                case red:
                    std::cout << "\033[91m";
                    break;
                case green:
                    std::cout << "\033[92m";
                    break;
                case orange:
                    std::cout << "\033[38;5;208m";
                    break;
            }
            if (j % row_of_squares == 0 && j > 0) {
                std::cout << "│ ";
            }
            std::cout << cube_side_order[(j / row_of_squares) + 1]->getSquare(j % row_of_squares) << "\033[0m" << " ";

        }
        std::cout << "│";
        if (i != col_of_squares - 1) {
            std::cout << "\n├───┼───┼───┤ ├───┼───┼───┤ ├───┼───┼───┤ ├───┼───┼───┤\n";
        }

    }
    std::cout << "\n└───┴───┴───┘ └───┴───┴───┘ └───┴───┴───┘ └───┴───┴───┘" << '\n';

    down->printSide();
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

