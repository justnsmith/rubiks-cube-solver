#include <bits/stdc++.h>
using namespace std;

void printVec(const std::array<int, 9>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

// 0 1 2 3 4 5 6 7 8
// 4 4 4 1 3 1 2 2 2

// 2 5 8 1 4 7 0 3 6
// 4 1 2 4 3 2 4 1 2


// 4 4 4
// 1 3 1
// 2 2 2

// 2 1 4
// 2 3 4
// 2 1 4

// 6 3 0
// 7 4 1
// 8 5 2

// 6 3 0 7 4 1 8 5 2


int main() {
    std::array<int, 9> arr = {0,1,2,3,4,5,6,7,8};
    std::array<int, 9> newArr = {};
    const int spacing = 3;
    int currIndex = 6;
    int storedIndex = 6;
    for (int i = 0; i < arr.size(); i++) {
        std::cout << currIndex << std::endl;
        if (i > 0 && i % 3 == 0) {
            storedIndex += 1;
            currIndex = storedIndex;
        }
        newArr[i] = arr[currIndex];
        currIndex -= spacing;
    }
    printVec(newArr);
}
