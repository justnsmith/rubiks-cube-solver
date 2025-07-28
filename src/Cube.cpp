#include <Cube.h>
#include <iostream>

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
    const std::array<Side*, NUM_OF_BODY_SIDES> cube_side_order = {left, front, back, right};
    const int row_of_squares = SIDE_LENGTH;
    const int col_of_squares = SIDE_LENGTH;

    std::cout << '\n';
    up->printSide();

    std::cout << "┌───┬───┬───┐ ┌───┬───┬───┐ ┌───┬───┬───┐ ┌───┬───┬───┐" << '\n';
    for (int i = 0; i < col_of_squares; i++) {
        for (int j = 0; j < row_of_squares * NUM_OF_BODY_SIDES; j++) {
            std::cout << "│ ";

            switch (cube_side_order[(j / row_of_squares)]->getSquare((j % row_of_squares) + (i * SIDE_LENGTH))) {
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

void Cube::inverse_move(Side* side, const std::array<int, SIDE_LENGTH>& original_squares, const std::array<int, SIDE_LENGTH>& new_squares) {
    Colors temp {};

    if (original_squares[0] == new_squares[2] && original_squares[2] == new_squares[0]) {
        temp = side->getSquare(original_squares[0]);
        side->getSquare(original_squares[0]) = side->getSquare(original_squares[2]);
        side->getSquare(original_squares[2]) = temp;
    }
    else {
        for (int i = 0; i < original_squares.size(); i++) {
            temp = side->getSquare(original_squares[i]);
            side->getSquare(original_squares[i]) = side->getSquare(new_squares[i]);
            side->getSquare(new_squares[i]) = temp;
    }
    }
}

void Cube::makeTurn(const std::array<Side*, NUM_OF_BODY_SIDES>& relevant_sides, const std::array<int, SIDE_LENGTH>& square_positions) {
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

void Cube::rotateHelper(const std::array<Side*, NUM_OF_BODY_SIDES>& relevant_sides) {
    Side temp {};
    for (int i = 1; i < relevant_sides.size(); i++) {
        temp = *relevant_sides[0];
        *relevant_sides[0] = *relevant_sides[i];
        *relevant_sides[i] = temp;
    }
}

void Cube::rotate_side_counterclockwise(Side* side) {
    std::array<Colors, NUM_OF_SQUARES> newSide = {};
    const int spacing = SIDE_LENGTH;
    int currIndex = 2;
    int storedIndex = 2;

    for (int i = 0; i < NUM_OF_SQUARES; i++) {
        if (i > 0 && i % SIDE_LENGTH == 0) {
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
    const int spacing = SIDE_LENGTH;
    int currIndex = 6;
    int storedIndex = 6;
    for (int i = 0; i < NUM_OF_SQUARES; i++) {
        if (i > 0 && i % SIDE_LENGTH == 0) {
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
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {down, front, up, back};

    inverse_move(back, {6,7,8}, {2,1,0});
    inverse_move(back, {3,4,5}, {5,4,3});
    rotateHelper(relevant_sides);
    inverse_move(back, {6,7,8}, {2,1,0});
    inverse_move(back, {3,4,5}, {5,4,3});
    rotate_side_clockwise(right);
    rotate_side_counterclockwise(left);
}

void Cube::rotate_down() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {back, up, front, down};

    inverse_move(back, {6,7,8}, {2,1,0});
    inverse_move(back, {3,4,5}, {5,4,3});
    rotateHelper(relevant_sides);
    inverse_move(back, {6,7,8}, {2,1,0});
    inverse_move(back, {3,4,5}, {5,4,3});
    rotate_side_clockwise(left);
    rotate_side_counterclockwise(right);
}

void Cube::rotate_left() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {right, back, left, front};

    rotateHelper(relevant_sides);
    rotate_side_clockwise(down);
    rotate_side_counterclockwise(up);
}

void Cube::rotate_right() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {front, left, back, right};

    rotateHelper(relevant_sides);
    rotate_side_clockwise(up);
    rotate_side_counterclockwise(down);
}

void Cube::left_up() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {down, front, up, back};
    const std::array<int, SIDE_LENGTH> left_side_squares = {0, 3, 6};

    inverse_move(back, left_side_squares, {8, 5, 2});
    makeTurn(relevant_sides, left_side_squares);
    inverse_move(back, left_side_squares, {8, 5, 2});
    rotate_side_counterclockwise(left);
}

void Cube::left_down() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {back, up, front, down};
    const std::array<int, SIDE_LENGTH> left_side_squares = {0, 3, 6};

    inverse_move(back, left_side_squares, {8, 5, 2});
    makeTurn(relevant_sides, left_side_squares);
    inverse_move(back, left_side_squares, {8, 5, 2});
    rotate_side_clockwise(left);
}

void Cube::right_up() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {down, front, up, back};
    const std::array<int, SIDE_LENGTH> right_side_squares = {2, 5, 8};

    inverse_move(back, right_side_squares, {6, 3, 0});
    makeTurn(relevant_sides, right_side_squares);
    inverse_move(back, right_side_squares, {6, 3, 0});
    rotate_side_clockwise(right);
}

void Cube::right_down() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {back, up, front, down};
    const std::array<int, SIDE_LENGTH> right_side_squares = {2, 5, 8};

    inverse_move(back, right_side_squares, {6, 3, 0});
    makeTurn(relevant_sides, right_side_squares);
    inverse_move(back, right_side_squares, {6, 3, 0});
    rotate_side_counterclockwise(right);
}

void Cube::middle_up() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {down, front, up, back};
    const std::array<int, SIDE_LENGTH> middle_side_squares = {1, 4, 7};

    inverse_move(back, middle_side_squares, {7, 4, 1});
    makeTurn(relevant_sides, middle_side_squares);
    inverse_move(back, middle_side_squares, {7, 4, 1});
}

void Cube::middle_down() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {back, up, front, down};
    const std::array<int, SIDE_LENGTH> middle_side_squares = {1, 4, 7};

    inverse_move(back, middle_side_squares, {7, 4, 1});
    makeTurn(relevant_sides, middle_side_squares);
    inverse_move(back, middle_side_squares, {7, 4, 1});
}

void Cube::middle_left() {
   const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {front, left, back, right};
   const std::array<int, SIDE_LENGTH> middle_side_squares = {3, 4, 5};

   makeTurn(relevant_sides, middle_side_squares);
}

void Cube::middle_right() {
   const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {right, back, left, front};
   const std::array<int, SIDE_LENGTH> middle_side_squares = {3, 4, 5};

   makeTurn(relevant_sides, middle_side_squares);
}

void Cube::top_left() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {front, left, back, right};
    const std::array<int, SIDE_LENGTH> top_side_squares = {0, 1, 2};

    makeTurn(relevant_sides, top_side_squares);
    rotate_side_clockwise(up);
}

void Cube::top_right() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {right, back, left, front};
    const std::array<int, SIDE_LENGTH> top_side_squares = {0, 1, 2};

    makeTurn(relevant_sides, top_side_squares);
    rotate_side_counterclockwise(up);
}

void Cube::bottom_left() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {front, left, back, right};
    const std::array<int, SIDE_LENGTH> top_side_squares = {6, 7, 8};

    makeTurn(relevant_sides, top_side_squares);
    rotate_side_counterclockwise(down);
}

void Cube::bottom_right() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {right, back, left, front};
    const std::array<int, SIDE_LENGTH> top_side_squares = {6, 7, 8};

    makeTurn(relevant_sides, top_side_squares);
    rotate_side_clockwise(down);
}

void Cube::front_right() {
    rotate_right();
    left_down();
    rotate_left();
}

void Cube::front_left() {
    rotate_left();
    right_down();
    rotate_right();
}

void Cube::back_right() {
    rotate_right();
    right_down();
    rotate_left();
}

void Cube::back_left() {
    rotate_left();
    left_down();
    rotate_right();
}
