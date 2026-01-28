# Rubik's Cube Solver

A C++ implementation of a 3x3 Rubik's Cube simulator and solver using the beginner's method.

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Building](#building)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running](#running)
  - [Cleaning](#cleaning)
- [Cube Representation](#cube-representation)
- [Move Notation](#move-notation)
  - [Face Moves](#face-moves)
  - [Slice Moves](#slice-moves)
  - [Cube Rotations](#cube-rotations)
- [Implementation Details](#implementation-details)
  - [Class Structure](#class-structure)
  - [Key Features](#key-features)
  - [Algorithm Components](#algorithm-components)
- [Current Status](#current-status)
- [Usage Example](#usage-example)
- [Technical Highlights](#technical-highlights)
- [Future Enhancements](#future-enhancements)
- [Author](#author)

## Features

- **Visual Cube Representation**: Color-coded terminal output with ASCII art borders
- **Cube Manipulation**: Complete set of rotation operations (face turns, slice moves, cube rotations)
- **Scrambling**: Random scramble generation with move notation output
- **Automatic Solving**: Implementation of the beginner's method (currently solving white cross)
- **Move Tracking**: Real-time display of moves during scrambling

## Project Structure

```
.
├── include/
│   ├── Cube.h          # Main cube class definition
│   └── Side.h          # Side class and enums
├── src/
│   ├── Cube.cpp        # Cube implementation
│   ├── Side.cpp        # Side implementation
│   └── main.cpp        # Entry point
├── Makefile            # Build configuration
└── README.md           # This file
```

## Building

### Prerequisites
- C++17 compatible compiler (g++)
- Make utility
- Terminal with ANSI color support

### Compilation
```bash
make
```

### Running
```bash
make run
```

### Cleaning
```bash
make clean
```

## Cube Representation

The cube uses a standard color scheme:
- **Yellow**: Top face
- **White**: Bottom face
- **Blue**: Left face
- **Red**: Front face
- **Green**: Right face
- **Orange**: Back face

## Move Notation

The solver uses the following move notation:

### Face Moves
- `LU` / `LD` - Left face up/down
- `RU` / `RD` - Right face up/down
- `TL` / `TR` - Top face left/right
- `BOL` / `BOR` - Bottom face left/right
- `FL` / `FR` - Front face left/right
- `BAL` / `BAR` - Back face left/right

### Slice Moves
- `MU` / `MD` - Middle slice up/down
- `ML` / `MR` - Middle slice left/right

### Cube Rotations
- `rotate_up()` / `rotate_down()` - Rotate entire cube vertically
- `rotate_left()` / `rotate_right()` - Rotate entire cube horizontally

## Implementation Details

### Class Structure

#### `Side` Class
- Represents a single face of the cube
- Contains 9 squares in a 3x3 grid
- Provides color-coded printing functionality
- Uses enums for colors and square positions

#### `Cube` Class
- Manages 6 sides and their relationships
- Tracks side positions (up, down, left, right, front, back)
- Maintains color-to-side mapping for dynamic tracking
- Implements all cube operations and solving algorithms

### Key Features

**State Management**: The cube maintains pointers to each face and updates them dynamically during cube rotations, ensuring correct orientation tracking.

**Visual Output**: Uses ANSI escape codes for colorized terminal output, displaying the cube in an unfolded net pattern.

**Solving Algorithm**: Currently implements the first stage of the beginner's method:
1. **White Cross**: Positions white edge pieces correctly on the bottom face with matching side colors

### Algorithm Components

**Helper Functions**:
- `find_missing_white_edge()`: Locates white edge pieces not yet in position
- `find_missing_white_corner()`: Locates white corner pieces for subsequent solving stages
- `turnTopUntil()`: Rotates the top face until a condition is met
- `makeTurn()`: Executes a single turn affecting multiple sides
- `inverse_move()`: Handles special orientation swaps for back face moves

## Current Status

✅ **Implemented**:
- Complete cube manipulation
- White cross solving (stage 1 of beginner's method)
- Visual representation
- Scrambling with 25 random moves
- Move notation output

🚧 **In Progress**:
- White corners (stage 2)
- Middle layer edges (stage 3)
- Yellow cross (stage 4)
- Yellow corners position (stage 5)
- Yellow corners orientation (stage 6)
- Final layer edges (stage 7)

## Usage Example

```cpp
#include <Cube.h>

int main() {
    Cube cube;

    // Display initial state
    cube.printCube();

    // Scramble the cube
    cube.scramble();

    // Display scrambled state
    cube.printCube();

    // Solve the cube
    cube.solve();

    // Display solved state
    cube.printCube();

    return 0;
}
```

## Technical Highlights

- **Efficient State Tracking**: Uses pointer-based side management for O(1) orientation queries
- **Modular Design**: Separates concerns between side representation and cube logic
- **Functional Callbacks**: Uses `std::function` for flexible condition-based operations
- **Template-Based Rotation**: Generalizes rotation logic across different move types

## Future Enhancements

- Complete beginner's method implementation
- Advanced solving algorithms (CFOP, Roux)
- Move optimization and analysis
- GUI interface
- 2x2 and 4x4 cube support
- Solution verification
- Performance benchmarking

## Author

Created as a demonstration of algorithm implementation and C++ programming concepts.
