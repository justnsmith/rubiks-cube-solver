#include <iostream>
#include <Cube.h>

using namespace std;

int main() {
    Cube cube;
    cube.test();
}

// 0 1 2
// 3 4 5
// 6 7 8

// 2 5 8
// 1 4 7
// 0 3 6

// 0 1 2 3 4 5 6 7 8
// 2 5 8 1 4 7 0 3 6

// arr[0] = side[6]
// arr[1] = side[3]
// arr[2] = side[0]
// arr[3] = side[7]
// arr[4] = side[4]
// arr[5] = side[1]
// arr[6] = side[8]
// arr[7] = side[5]
// arr[8] = side[6]

// Side = [i % 3]
