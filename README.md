# Tetris Game

## Introduction
This is a terminal-based implementation of the classic Tetris game in C++. It features shape stacking, collision detection, and a scoring system, providing an engaging and interactive gaming experience.

## Controls
- **Move Left**: `A` or Left Arrow (`←`)
- **Move Right**: `D` or Right Arrow (`→`)
- **Rotate Shape**: `W` or Up Arrow (`↑`)
- **Soft Drop**: `S` or Down Arrow (`↓`)
- **Hard Drop**: `Space`
- **Quit Game**: `ESC`

## Game Mechanics
- The player controls tetrominoes that fall from the top of the grid.
- The objective is to arrange these tetrominoes to form complete horizontal lines.
- Completed lines disappear, and the player earns points.
- The game speeds up as the player clears more lines.
- The game ends when the tetrominoes stack up to the top of the grid.

## Implementation Details
### 1. **Game Grid**
- The playing field is a 22-row by 12-column grid.
- Borders are marked with `*`, and empty spaces are represented by `' '`.
- Completed lines are cleared, and remaining blocks shift down.

### 2. **Tetrominoes**
- There are 7 different tetromino shapes (I, O, T, S, Z, J, L), each with four possible rotations.
- Shapes are represented as 4×4 arrays.
- Shapes rotate unless a rotation causes a collision.

### 3. **Collision Detection**
- The game checks for collisions when moving or rotating a tetromino.
- If movement would cause overlap with an existing block or the border, it is prevented.
- When a tetromino reaches the bottom or another shape, it becomes part of the grid.

### 4. **Scoring System**
- Completing a line grants `10` points.
- Every `2` lines cleared increases the level.
- Higher levels increase the game speed.

### 5. **Game Speed**
- The fall speed starts at `500ms` per step.
- Speed decreases as the level increases, with a minimum of `100ms` per step.

### 6. **Graphics and Display**
- The console color is set dynamically to differentiate between elements.
- The cursor is hidden for a smoother experience.
- Game information (Score, Level, Lines Cleared) is displayed on the side.

## Getting Started
### **Compilation and Execution**
1. Ensure you have a C++ compiler installed (MinGW, MSVC, etc.).
2. Compile the program using:
   ```sh
   g++ tetris.cpp -o tetris.exe
   ```
3. Run the game:
   ```sh
   tetris.exe
   ```

## Features to Add
- **Hold and Swap Mechanism**: Allow players to hold a piece for later use.
- **Additional Game Modes**: Timed or challenge modes.
- **Improved UI**: Graphical enhancements for better visibility.

Enjoy playing Tetris! 🎮

