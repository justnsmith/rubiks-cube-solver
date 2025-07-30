#include <Cube.h>
#include <iostream>

Cube::Cube() {
    initailizeCube();
}

void Cube::initailizeCube() {
    for (int side = 0; side < NUM_OF_SIDES; side++) {
        Colors current_side = static_cast<Colors> (side);
        switch (current_side) {
            case yellow:
                up = &sides[current_side];
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
        color_to_side[current_side] = &sides[side];
        for (int square = 0; square < NUM_OF_SQUARES; square++) {
            sides[side].getSquare(square) = current_side;
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
    return *(color_to_side[color]);
}

const std::string Cube::colorsToString(Colors color) {
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
    changeSideColor(relevant_sides);
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
    changeSideColor(relevant_sides);
}

void Cube::rotate_left() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {front, left, back, right};

    rotateHelper(relevant_sides);
    rotate_side_clockwise(up);
    rotate_side_counterclockwise(down);
    changeSideColor(relevant_sides);
}

void Cube::rotate_right() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {right, back, left, front};

    rotateHelper(relevant_sides);
    rotate_side_clockwise(down);
    rotate_side_counterclockwise(up);
    changeSideColor(relevant_sides);
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
    changeSideColor(relevant_sides);
}

void Cube::middle_down() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {back, up, front, down};
    const std::array<int, SIDE_LENGTH> middle_side_squares = {1, 4, 7};

    inverse_move(back, middle_side_squares, {7, 4, 1});
    makeTurn(relevant_sides, middle_side_squares);
    inverse_move(back, middle_side_squares, {7, 4, 1});
    changeSideColor(relevant_sides);
}

void Cube::middle_left() {
   const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {front, left, back, right};
   const std::array<int, SIDE_LENGTH> middle_side_squares = {3, 4, 5};

   makeTurn(relevant_sides, middle_side_squares);
   changeSideColor(relevant_sides);
}

void Cube::middle_right() {
   const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {right, back, left, front};
   const std::array<int, SIDE_LENGTH> middle_side_squares = {3, 4, 5};

   makeTurn(relevant_sides, middle_side_squares);
   changeSideColor(relevant_sides);
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
    rotate_left();
    left_down();
    rotate_right();
}

void Cube::front_left() {
    rotate_right();
    right_down();
    rotate_left();
}

void Cube::back_right() {
    rotate_left();
    right_down();
    rotate_right();
}

void Cube::back_left() {
    rotate_right();
    left_down();
    rotate_left();
}

void Cube::scramble() {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 25; i++) {
        int randomMove = (rand() % 16) + 1;
        switch (randomMove) {
            case 1:
                left_up();
                std::cout << "LU ";
                break;
            case 2:
                left_down();
                std::cout << "LD ";
                break;
            case 3:
                right_up();
                std::cout << "RU ";
                break;
            case 4:
                right_down();
                std::cout << "RD ";
                break;
            case 5:
                middle_up();
                std::cout << "MU ";
                break;
            case 6:
                middle_down();
                std::cout << "MD ";
                break;
            case 7:
                middle_left();
                std::cout << "ML ";
                break;
            case 8:
                middle_right();
                std::cout << "MR ";
                break;
            case 9:
                top_left();
                std::cout << "TL ";
                break;
            case 10:
                top_right();
                std::cout << "TR ";
                break;
            case 11:
                bottom_left();
                std::cout << "BOL ";
                break;
            case 12:
                bottom_right();
                std::cout << "BOR ";
                break;
            case 13:
                front_right();
                std::cout << "FR ";
                break;
            case 14:
                front_left();
                std::cout << "FL ";
                break;
            case 15:
                back_right();
                std::cout << "BAR ";
                break;
            case 16:
                back_left();
                std::cout << "BAL ";
                break;
        }
    }
    std::cout << '\n';
}

void Cube::changeSideColor(const std::array<Side*, NUM_OF_BODY_SIDES>& relevant_sides) {
    for (int i = 0; i < NUM_OF_BODY_SIDES; i++) {
        color_to_side[relevant_sides[i]->getSquare(4)] = relevant_sides[i];
    }
}

const std::string Cube::sideToPosition(Side* side) {
    if (side == up) return "up";
    if (side == down) return "down";
    if (side == left) return "left";
    if (side == right) return "right";
    if (side == front) return "front";
    if (side == back) return "back";
    return "unknown";
}

void Cube::whiteCross() {
    std::string curr_yellow_side = sideToPosition(&(getSide(static_cast<Side::Colors>(yellow))));
    const std::array<int, 4> relevant_squares {1,3,5,7};
    int curr_amount {};

    if (curr_yellow_side == "left") {
        rotate_right();
        rotate_up();
    }
    else if (curr_yellow_side == "front") {
        rotate_up();
    }
    else if (curr_yellow_side == "back") {
        rotate_down();
    }
    else if (curr_yellow_side == "right") {
        rotate_left();
        rotate_up();
    }
    else if (curr_yellow_side == "down") {
        rotate_up();
        rotate_up();
    }

    for (int i = 0; i < relevant_squares.size(); i++) {
        if (white == getSide(yellow).getSquare(relevant_squares[i])) {
            curr_amount++;
        }
    }

    printCube();

    for (int i = 1; i < NUM_OF_SIDES; i++) {
        for (int j = 0; j < relevant_squares.size(); j++) {
            if (curr_amount == 4) {
                break;
            }

            if (color_to_side[static_cast<Colors> (i)] == &getSide(white)) {
                if (white == getSide(white).getSquare(relevant_squares[j])) {
                    if (relevant_squares[j] == 1) {
                        while (white == getSide(yellow).getSquare(7)) {
                            top_left();
                        }
                        front_left();
                        front_left();
                    }
                    else if (relevant_squares[j] == 3) {
                        while (white == getSide(yellow).getSquare(3)) {
                            top_left();
                        }
                        left_up();
                        left_up();
                    }
                    else if (relevant_squares[j] == 5) {
                        while (white == getSide(yellow).getSquare(5)) {
                            top_left();
                        }
                        right_up();
                        right_up();
                    }
                    else {
                        while (white == getSide(yellow).getSquare(1)) {
                            top_left();
                        }
                        back_left();
                        back_left();
                    }
                    curr_amount++;
                }
            }
            else if (color_to_side[static_cast<Colors> (i)] == front) {
                if (white == front->getSquare(relevant_squares[j])) {
                    if (relevant_squares[j] == 1) {
                        while (white == getSide(yellow).getSquare(7)) {
                            if (left->getSquare(5) != white) {
                                front_left();
                                while (getSide(yellow).getSquare(3) == white) {
                                    top_left();
                                }
                                left_up();
                                curr_amount++;
                            }
                            else if (right->getSquare(3) != white) {
                                front_right();
                                while (getSide(yellow).getSquare(3) == white) {
                                    top_left();
                                }
                                right_up();
                                curr_amount++;
                            }
                            else {
                                while (getSide(yellow).getSquare(3) == white) {
                                    top_left();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Cube::solve() {
    whiteCross();
}
