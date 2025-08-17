#include <Cube.h>
#include <iostream>

Cube::Cube() {
    initailizeCube();
}

bool operator==(const Cube& lhs, const Cube& rhs) {
    for (int i = 0; i < NUM_OF_SIDES; i++) {
        for (int j = 0; j < NUM_OF_SQUARES; j++) {
            if (lhs.getSide(static_cast<Side::Colors> (i)).getSquare(static_cast<Side::SquarePosition> (j)) != rhs.getSide(static_cast<Side::Colors> (i)).getSquare(static_cast<Side::SquarePosition> (j))) {
                return false;
            }
        }
    }
    return true;
}

void Cube::initailizeCube() {
    for (int side = 0; side < NUM_OF_SIDES; side++) {
        Colors current_side = static_cast<Colors> (side);
        switch (current_side) {
            case Yellow:
                up = &sides[current_side];
                break;
                case White:
                down = &sides[side];
                break;
                case Blue:
                left = &sides[side];
                break;
                case Red:
                front = &sides[side];
                break;
                case Green:
                right = &sides[side];
                break;
                case Orange:
                back = &sides[side];
                break;
            }
            color_to_side[current_side] = &sides[side];
            for (int square = TopLeftCorner; square < NUM_OF_SQUARES; square++) {
                sides[side].getSquare(static_cast<SquarePosition> (square)) = current_side;
            }
        }
    }

    void Cube::printCube() const {
        const std::array<Side*, NUM_OF_BODY_SIDES> cube_side_order = {left, front, back, right};
    const int row_of_squares = SIDE_LENGTH;
    const int col_of_squares = SIDE_LENGTH;

    std::cout << '\n';
    up->printSide();

    std::cout << "┌───┬───┬───┐ ┌───┬───┬───┐ ┌───┬───┬───┐ ┌───┬───┬───┐" << '\n';
    for (int i = 0; i < col_of_squares; i++) {
        for (int j = 0; j < row_of_squares * NUM_OF_BODY_SIDES; j++) {
            std::cout << "│ ";

            switch (cube_side_order[(j / row_of_squares)]->getSquare(static_cast<SquarePosition>((j % row_of_squares) + (i * SIDE_LENGTH)))) {
                case Yellow:
                    std::cout << "\033[93m";
                    break;
                case White:
                    std::cout << "\033[97m";
                    break;
                case Blue:
                    std::cout << "\033[94m";
                    break;
                case Red:
                    std::cout << "\033[91m";
                    break;
                case Green:
                    std::cout << "\033[92m";
                    break;
                case Orange:
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

Cube::Side& Cube::getSide(Colors color) const {
    return *(color_to_side.at(color));
}

const std::string Cube::colorsToString(Colors color) {
    switch (color) {
        case Colors::Yellow: return "yellow";
        case Colors::White: return "white";
        case Colors::Blue: return "blue";
        case Colors::Red: return "red";
        case Colors::Green: return "green";
        case Colors::Orange: return "orange";
    }
}

void Cube::inverse_move(Side* side, const std::array<SquarePosition, SIDE_LENGTH>& original_squares, const std::array<SquarePosition, SIDE_LENGTH>& new_squares) {
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

void Cube::makeTurn(const std::array<Side*, NUM_OF_BODY_SIDES>& relevant_sides, const std::array<SquarePosition, SIDE_LENGTH>& square_positions) {
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

    for (int i = TopLeftCorner; i < NUM_OF_SQUARES; i++) {
        if (i > 0 && i % SIDE_LENGTH == 0) {
            storedIndex -= 1;
            currIndex = storedIndex;
        }
        newSide[i] = side->getSquare(static_cast<SquarePosition> (currIndex));
        currIndex += spacing;
    }

    for (int i = TopLeftCorner; i < NUM_OF_SQUARES; i++) {
        side->getSquare(static_cast<SquarePosition>(i)) = newSide[i];
    }
}

void Cube::rotate_side_clockwise(Side* side) {
    std::array<Colors, NUM_OF_SQUARES> newSide = {};
    const int spacing = SIDE_LENGTH;
    int currIndex = 6;
    int storedIndex = 6;
    for (int i = TopLeftCorner; i < NUM_OF_SQUARES; i++) {
        if (i > 0 && i % SIDE_LENGTH == 0) {
            storedIndex += 1;
            currIndex = storedIndex;
        }
        newSide[i] = side->getSquare(static_cast<SquarePosition> (currIndex));
        currIndex -= spacing;
    }

    for (int i = TopLeftCorner; i < NUM_OF_SQUARES; i++) {
        side->getSquare(static_cast<SquarePosition> (i)) = newSide[i];
    }
}

void Cube::rotate_up() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {down, front, up, back};

    inverse_move(back, {BottomLeftCorner, BottomEdge, BottomRightCorner}, {TopRightCorner, TopEdge, TopLeftCorner});
    inverse_move(back, {LeftEdge, Middle, RightEdge}, {RightEdge, Middle, LeftEdge});
    rotateHelper(relevant_sides);
    inverse_move(back, {BottomLeftCorner, BottomEdge, BottomRightCorner}, {TopRightCorner, TopEdge, TopLeftCorner});
    inverse_move(back, {LeftEdge, Middle, RightEdge}, {RightEdge, Middle, LeftEdge});
    rotate_side_clockwise(right);
    rotate_side_counterclockwise(left);
    changeSideColor(relevant_sides);
}

void Cube::rotate_down() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {back, up, front, down};

    inverse_move(back, {BottomLeftCorner, BottomEdge, BottomRightCorner}, {TopRightCorner, TopEdge, TopLeftCorner});
    inverse_move(back, {LeftEdge, Middle, RightEdge}, {RightEdge, Middle, LeftEdge});
    rotateHelper(relevant_sides);
    inverse_move(back, {BottomLeftCorner, BottomEdge, BottomRightCorner}, {TopRightCorner, TopEdge, TopLeftCorner});
    inverse_move(back, {LeftEdge, Middle, RightEdge}, {RightEdge, Middle, LeftEdge});
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
    const std::array<SquarePosition, SIDE_LENGTH> left_side_squares = {TopLeftCorner, LeftEdge, BottomLeftCorner};

    inverse_move(back, left_side_squares, {BottomRightCorner, RightEdge, TopRightCorner});
    makeTurn(relevant_sides, left_side_squares);
    inverse_move(back, left_side_squares, {BottomRightCorner, RightEdge, TopRightCorner});
    rotate_side_counterclockwise(left);
}

void Cube::left_down() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {back, up, front, down};
    const std::array<SquarePosition, SIDE_LENGTH> left_side_squares = {TopLeftCorner, LeftEdge, BottomLeftCorner};

    inverse_move(back, left_side_squares, {BottomRightCorner, RightEdge, TopRightCorner});
    makeTurn(relevant_sides, left_side_squares);
    inverse_move(back, left_side_squares, {BottomRightCorner, RightEdge, TopRightCorner});
    rotate_side_clockwise(left);
}

void Cube::right_up() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {down, front, up, back};
    const std::array<SquarePosition, SIDE_LENGTH> right_side_squares = {TopRightCorner, RightEdge, BottomRightCorner};

    inverse_move(back, right_side_squares, {BottomLeftCorner, LeftEdge, TopLeftCorner});
    makeTurn(relevant_sides, right_side_squares);
    inverse_move(back, right_side_squares, {BottomLeftCorner, LeftEdge, TopLeftCorner});
    rotate_side_clockwise(right);
}

void Cube::right_down() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {back, up, front, down};
    const std::array<SquarePosition, SIDE_LENGTH> right_side_squares = {TopRightCorner, RightEdge, BottomRightCorner};

    inverse_move(back, right_side_squares, {BottomLeftCorner, LeftEdge, TopLeftCorner});
    makeTurn(relevant_sides, right_side_squares);
    inverse_move(back, right_side_squares, {BottomLeftCorner, LeftEdge, TopLeftCorner});
    rotate_side_counterclockwise(right);
}

void Cube::middle_up() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {down, front, up, back};
    const std::array<SquarePosition, SIDE_LENGTH> middle_side_squares = {TopEdge, Middle, BottomEdge};

    inverse_move(back, middle_side_squares, {BottomEdge, Middle, TopEdge});
    makeTurn(relevant_sides, middle_side_squares);
    inverse_move(back, middle_side_squares, {BottomEdge, Middle, TopEdge});
    changeSideColor(relevant_sides);
}

void Cube::middle_down() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {back, up, front, down};
    const std::array<SquarePosition, SIDE_LENGTH> middle_side_squares = {TopEdge, Middle, BottomEdge};

    inverse_move(back, middle_side_squares, {BottomEdge, Middle, TopEdge});
    makeTurn(relevant_sides, middle_side_squares);
    inverse_move(back, middle_side_squares, {BottomEdge, Middle, TopEdge});
    changeSideColor(relevant_sides);
}

void Cube::middle_left() {
   const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {front, left, back, right};
   const std::array<SquarePosition, SIDE_LENGTH> middle_side_squares = {LeftEdge, Middle, RightEdge};

   makeTurn(relevant_sides, middle_side_squares);
   changeSideColor(relevant_sides);
}

void Cube::middle_right() {
   const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {right, back, left, front};
   const std::array<SquarePosition, SIDE_LENGTH> middle_side_squares = {LeftEdge, Middle, RightEdge};

   makeTurn(relevant_sides, middle_side_squares);
   changeSideColor(relevant_sides);
}

void Cube::top_left() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {front, left, back, right};
    const std::array<SquarePosition, SIDE_LENGTH> top_side_squares = {TopLeftCorner, TopEdge, TopRightCorner};

    makeTurn(relevant_sides, top_side_squares);
    rotate_side_clockwise(up);
}

void Cube::top_right() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {right, back, left, front};
    const std::array<SquarePosition, SIDE_LENGTH> top_side_squares = {TopLeftCorner, TopEdge, TopRightCorner};

    makeTurn(relevant_sides, top_side_squares);
    rotate_side_counterclockwise(up);
}

void Cube::bottom_left() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {front, left, back, right};
    const std::array<SquarePosition, SIDE_LENGTH> top_side_squares = {BottomLeftCorner, BottomEdge, BottomRightCorner};

    makeTurn(relevant_sides, top_side_squares);
    rotate_side_counterclockwise(down);
}

void Cube::bottom_right() {
    const std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {right, back, left, front};
    const std::array<SquarePosition, SIDE_LENGTH> top_side_squares = {BottomLeftCorner, BottomEdge, BottomRightCorner};

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
        color_to_side[relevant_sides[i]->getSquare(Middle)] = relevant_sides[i];
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

Cube::PieceLocation Cube::find_missing_white_edge() const {
    const std::array<SquarePosition, 4> relevant_squares = {TopEdge, LeftEdge, RightEdge, BottomEdge};
    for (int i = 0; i < NUM_OF_SIDES; i++) {
        for (int j = 0; j < relevant_squares.size(); j++) {
            if (getSide(static_cast<Colors> (i)).getSquare(relevant_squares[j]) == White && &getSide(static_cast<Colors> (i)) != &getSide(Yellow)) {
                return {i, static_cast<SquarePosition> (relevant_squares[j])};
            }
        }
    }
    return {-1, Middle};
}

void Cube::turnTopUntil(std::function<bool()> condition) {
    while (condition()) {
        top_left();
    }
}

void Cube::whiteCross() {
    // ROTATE CUBE SO YELLOW IS TOP
    if (&getSide(Yellow) == down) {
        rotate_up();
        rotate_up();
    }
    else if (&getSide(Yellow) == left) {
        rotate_right();
        rotate_up();
    }
    else if (&getSide(Yellow) == right) {
        rotate_left();
        rotate_up();
    }
    else if (&getSide(Yellow) == front) {
        rotate_up();
    }
    else if (&getSide(Yellow) == back) {
        rotate_down();
    }

    // DEVELOPING SUNFLOWER
    PieceLocation white_edge{};
    while ((white_edge = find_missing_white_edge()), white_edge.face != -1 || white_edge.pos != Middle) {
        if (&getSide(static_cast<Colors> (white_edge.face)) == down) {
            if (white_edge.pos == TopEdge) {
                turnTopUntil([&]() { return up->getSquare(BottomEdge) == White; });
                front_left();
                front_left();
            }
            else if (white_edge.pos == LeftEdge) {
                turnTopUntil([&]() { return up->getSquare(LeftEdge) == White; });
                left_up();
                left_up();
            }
            else if (white_edge.pos == RightEdge) {
                turnTopUntil([&]() { return up->getSquare(RightEdge) == White; });
                right_up();
                right_up();
            }
            else if (white_edge.pos == BottomEdge) {
                turnTopUntil([&]() { return up->getSquare(TopEdge) == White; });
                back_left();
                back_left();
            }
        }

        else if (&getSide(static_cast<Colors> (white_edge.face)) == left) {
            if (white_edge.pos == TopEdge) {
                left_up();
                turnTopUntil([&]() { return up->getSquare(TopEdge) == White; });
                back_right();
            }
            else if (white_edge.pos == LeftEdge) {
                turnTopUntil([&]() { return up->getSquare(TopEdge) == White; });
                back_right();
            }
            else if (white_edge.pos == RightEdge) {
                turnTopUntil([&]() { return up->getSquare(BottomEdge) == White; });
                front_right();
            }
            else if (white_edge.pos == BottomEdge) {
                turnTopUntil([&]() { return up->getSquare(LeftEdge) == White; });
                left_down();
                top_left();
                back_right();
            }
        }

        else if (&getSide(static_cast<Colors> (white_edge.face)) == front) {
            if (white_edge.pos == TopEdge) {
                front_left();
                turnTopUntil([&]() { return up->getSquare(LeftEdge) == White; });
                left_up();
            }
            else if (white_edge.pos == LeftEdge) {
                turnTopUntil([&]() { return up->getSquare(LeftEdge) == White; });
                left_up();
            }
            else if (white_edge.pos == RightEdge) {
                turnTopUntil([&]() { return up->getSquare(RightEdge) == White; });
                right_up();
            }
            else if (white_edge.pos == BottomEdge) {
                turnTopUntil([&]() { return up->getSquare(LeftEdge) == White; });
                front_right();
                top_left();
                left_up();
            }
        }

        else if (&getSide(static_cast<Colors> (white_edge.face)) == right) {
            if (white_edge.pos == TopEdge) {
                right_down();
                turnTopUntil([&]() { return up->getSquare(BottomEdge) == White; });
                front_left();
            }
            else if (white_edge.pos == LeftEdge) {
                turnTopUntil([&]() { return up->getSquare(BottomEdge) == White; });
                front_left();
            }
            else if (white_edge.pos == RightEdge) {
                turnTopUntil([&]() { return up->getSquare(TopEdge) == White; });
                back_left();
            }
            else if (white_edge.pos == BottomEdge) {
                turnTopUntil([&]() { return up->getSquare(RightEdge) == White; });
                right_down();
                top_left();
                back_left();
            }
        }
        else if (&getSide(static_cast<Colors> (white_edge.face)) == back) {
            if (white_edge.pos == TopEdge) {
                back_right();
                turnTopUntil([&]() { return up->getSquare(RightEdge) == White; });
                right_down();
            }
            else if (white_edge.pos == LeftEdge) {
                turnTopUntil([&]() { return up->getSquare(RightEdge) == White; });
                right_down();
            }
            else if (white_edge.pos == RightEdge) {
                turnTopUntil([&]() { return up->getSquare(LeftEdge) == White; });
                left_down();
            }
            else if (white_edge.pos == BottomEdge) {
                turnTopUntil([&]() { return up->getSquare(TopEdge) == White; });
                back_left();
                top_left();
                right_down();
            }
        }
    }

    std::array<Side*, NUM_OF_BODY_SIDES> relevant_sides = {left, front, right, back};
    for (int i = 0; i < NUM_OF_BODY_SIDES; i++) {
        if (relevant_sides[i] == left) {
            turnTopUntil([&]() { return (relevant_sides[i]->getSquare(TopEdge) != relevant_sides[i]->getSquare(Middle) || up->getSquare(LeftEdge) != White); });
            left_up();
            left_up();
        }
        else if (relevant_sides[i] == front) {
            turnTopUntil([&]() { return (relevant_sides[i]->getSquare(TopEdge) != relevant_sides[i]->getSquare(Middle) || up->getSquare(BottomEdge) != White); });
            front_left();
            front_left();
        }
        else if (relevant_sides[i] == right) {
            turnTopUntil([&]() { return (relevant_sides[i]->getSquare(TopEdge) != relevant_sides[i]->getSquare(Middle) || up->getSquare(RightEdge) != White); });
            right_up();
            right_up();
        }
        else if (relevant_sides[i] == back) {
            turnTopUntil([&]() { return (relevant_sides[i]->getSquare(TopEdge) != relevant_sides[i]->getSquare(Middle) || up->getSquare(TopEdge) != White); });
            back_left();
            back_left();
        }
    }
}

void Cube::solve() {
    whiteCross();
}
