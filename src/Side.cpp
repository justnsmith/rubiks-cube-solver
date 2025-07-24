#include <Side.h>
#include <iostream>

Side::Colors& Side::getSquare(int index) {
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
        switch (getSquare(square)) {
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
        std::cout << getSquare(square) << "\033[0m" << " ";

        if (square % static_cast<int>(sqrt(NUM_OF_SQUARES)) == static_cast<int>(sqrt(NUM_OF_SQUARES)) - 1) {
            std::cout << "│\n";
            if (square != NUM_OF_SQUARES-1) {
                std::cout << "                     ├───┼───┼───┤" << '\n';
            }
        }
    }
    std::cout << "                     └───┴───┴───┘" << '\n';
}
