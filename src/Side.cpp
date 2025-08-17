#include <Side.h>
#include <iostream>

Side::Colors& Side::getSquare(SquarePosition index) {
    return squares[index];
}

void Side::printSide() {
    std::cout << "                     ┌───┬───┬───┐" << '\n';
    for (int square = 0; square < NUM_OF_SQUARES; square++) {
        if (square % 3 == 0) {
            std::cout << "                     │ ";
        }
        else {
            std::cout << "│ ";
        }
        switch (getSquare(static_cast<SquarePosition> (square))) {
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
        std::cout << "■" << "\033[0m" << " ";
        //std::cout << getSquare(square) << "\033[0m" << " ";

        if (square % static_cast<int>(sqrt(NUM_OF_SQUARES)) == static_cast<int>(sqrt(NUM_OF_SQUARES)) - 1) {
            std::cout << "│\n";
            if (square != NUM_OF_SQUARES-1) {
                std::cout << "                     ├───┼───┼───┤" << '\n';
            }
        }
    }
    std::cout << "                     └───┴───┴───┘" << '\n';
}
