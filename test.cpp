#include <bits/stdc++.h>
using namespace std;

void printVec(const std::array<int, 9>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}


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


// x 0 0
// x 0 0
// x 0 0

// 0 1 2 3 4 5 6 7 8
// 1 2 0 4 5 3 7 8 6

// 0 0 x
// 0 0 x
// 0 0 x
