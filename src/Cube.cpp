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
    const std::array<Side*, num_of_body_sides> cube_side_order = {left, front, back, right};
    const int row_of_squares = static_cast<int>(sqrt(NUM_OF_SQUARES));
    const int col_of_squares = static_cast<int>(sqrt(NUM_OF_SQUARES));
    std::cout << '\n';
    up->printSide();

    std::cout << "┌───┬───┬───┐ ┌───┬───┬───┐ ┌───┬───┬───┐ ┌───┬───┬───┐" << '\n';
    for (int i = 0; i < col_of_squares; i++) {
        for (int j = 0; j < row_of_squares * num_of_body_sides; j++) {
            std::cout << "│ ";

            switch (cube_side_order[(j / row_of_squares)]->getSquare((j % row_of_squares) + (i * 3))) {
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
            std::cout << "■" << "\033[0m" << " ";
            //std::cout << cube_side_order[(j / row_of_squares) + 1]->getSquare(j % row_of_squares) << "\033[0m" << " ";

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
    const std::array<int, 3> left_side_squares = {1, 2, 3};

    Colors temp {};
    for (int i = 0; i < left_side_squares.size(); i++) {
        temp = first_side.getSquare(left_side_squares[i]);
        std::cout << "Iteration: " << i << " Temp Value: " << temp << std::endl;
        std::cout << "  Before change: First Side Square " << left_side_squares[i] << ": " << first_side.getSquare(left_side_squares[i]) << std::endl;
        first_side.getSquare(left_side_squares[i]) = second_side.getSquare(left_side_squares[i]);
        std::cout << "  After change: First Side Square " << left_side_squares[i] << ": " << first_side.getSquare(left_side_squares[i]) << std::endl;
        std::cout << "  Before change: Second Side Square " << left_side_squares[i] << ": " << second_side.getSquare(left_side_squares[i]) << std::endl;
        second_side.getSquare(left_side_squares[i]) = temp;
        std::cout << "  After change: Second Side Square " << left_side_squares[i] << ": " << second_side.getSquare(left_side_squares[i]) << std::endl;
    }
}

void Cube::makeTurn(const std::array<Side*, 4>& relevant_sides, const std::array<int, 3>& square_positions) {
   Colors temp {};

    for (int i = 1; i < relevant_sides.size(); i++) {
        Side& currentSide = *relevant_sides[i];
        for (int j = 0; j < square_positions.size(); j++) {
            temp = relevant_sides[0]->getSquare(square_positions[j]);
            relevant_sides[0]->getSquare(square_positions[j]) = currentSide.getSquare(square_positions[j]);
            currentSide.getSquare(square_positions[j]) = temp;
        }
    }
}

void Cube::rotateHelper(const std::array<Side*, 4>& relevant_sides) {
    Side temp {};
    for (int i = 1; i < relevant_sides.size(); i++) {
        temp = *relevant_sides[0];
        *relevant_sides[0] = *relevant_sides[i];
        *relevant_sides[i] = temp;
    }
}

void Cube::rotate_side_counterclockwise(Side* side) {
    std::array<Colors, NUM_OF_SQUARES> newSide = {};
    const int spacing = 3;
    int currIndex = 2;
    int storedIndex = 2;

    for (int i = 0; i < NUM_OF_SQUARES; i++) {
        if (i > 0 && i % 3 == 0) {
            storedIndex -= 1;
            currIndex = storedIndex;
        }
        newSide[i] = side->getSquare(currIndex);
        currIndex += spacing;
    }

    for (int i = 0; i < NUM_OF_SQUARES; i++) {
        side->getSquare(i) = newSide[i];
    }
}

void Cube::rotate_side_clockwise(Side* side) {
    std::array<Colors, NUM_OF_SQUARES> newSide = {};
    const int spacing = 3;
    int currIndex = 6;
    int storedIndex = 6;
    for (int i = 0; i < NUM_OF_SQUARES; i++) {
        if (i > 0 && i % 3 == 0) {
            storedIndex += 1;
            currIndex = storedIndex;
        }
        newSide[i] = side->getSquare(currIndex);
        currIndex -= spacing;
    }

    for (int i = 0; i < NUM_OF_SQUARES; i++) {
        side->getSquare(i) = newSide[i];
    }
}

void Cube::rotate_up() {
    const std::array<Side*, 4> relevant_sides = {down, front, up, back};
    rotateHelper(relevant_sides);
}

void Cube::rotate_down() {
    const std::array<Side*, 4> relevant_sides = {back, up, front, down};
    rotateHelper(relevant_sides);
}

void Cube::rotate_left() {
    const std::array<Side*, 4> relevant_sides = {right, back, left, front};
    rotateHelper(relevant_sides);
    rotate_side_clockwise(down);
    rotate_side_counterclockwise(up);
}

void Cube::rotate_right() {
    const std::array<Side*, 4> relevant_sides = {front, left, back, right};
    rotateHelper(relevant_sides);
}

void Cube::left_up() {
    const std::array<Side*, 4> relevant_sides = {down, front, up, back};
    const std::array<int, 3> left_side_squares = {0, 3, 6};

    makeTurn(relevant_sides, left_side_squares);
}

void Cube::left_down() {
    const std::array<Side*, 4> relevant_sides = {back, up, front, down};
    const std::array<int, 3> left_side_squares = {0, 3, 6};

    makeTurn(relevant_sides, left_side_squares);
}

void Cube::right_up() {
    const std::array<Side*, 4> relevant_sides = {down, front, up, back};
    const std::array<int, 3> right_side_squares = {2, 5, 8};

    makeTurn(relevant_sides, right_side_squares);
}

void Cube::right_down() {
    const std::array<Side*, 4> relevant_sides = {back, up, front, down};
    const std::array<int, 3> right_side_squares = {2, 5, 8};

    makeTurn(relevant_sides, right_side_squares);
}

void Cube::middle_up() {
    const std::array<Side*, 4> relevant_sides = {down, front, up, back};
    const std::array<int, 3> middle_side_squares = {1, 4, 7};

    makeTurn(relevant_sides, middle_side_squares);
}

void Cube::middle_down() {
    const std::array<Side*, 4> relevant_sides = {back, up, front, down};
    const std::array<int, 3> middle_side_squares = {1, 4, 7};

    makeTurn(relevant_sides, middle_side_squares);
}

void Cube::top_left() {
    const std::array<Side*, 4> relevant_sides = {front, left, back, right};
    const std::array<int, 3> top_side_squares = {0, 1, 2};

    makeTurn(relevant_sides, top_side_squares);
}

void Cube::top_right() {
    const std::array<Side*, 4> relevant_sides = {right, back, left, front};
    const std::array<int, 3> top_side_squares = {0, 1, 2};

    makeTurn(relevant_sides, top_side_squares);
}

void Cube::bottom_left() {
    const std::array<Side*, 4> relevant_sides = {front, left, back, right};
    const std::array<int, 3> top_side_squares = {6, 7, 8};

    makeTurn(relevant_sides, top_side_squares);
}

void Cube::bottom_right() {
    const std::array<Side*, 4> relevant_sides = {right, back, left, front};
    const std::array<int, 3> top_side_squares = {6, 7, 8};

    makeTurn(relevant_sides, top_side_squares);
}

void Cube::front_right() {
    const std::array<Side*, 4> relevant_sides = {up, front, down, back};
    const std::array<int, 3> left_side_squares = {0, 3, 6};

    rotate_right();
    makeTurn(relevant_sides, left_side_squares);
    rotate_left();
}

void Cube::test() {
    left_up();
    right_up();
    top_left();
    bottom_right();

    front->printSide();
    rotate_side_clockwise(front);
    front->printSide();
    rotate_side_counterclockwise(front);
    front->printSide();
}
