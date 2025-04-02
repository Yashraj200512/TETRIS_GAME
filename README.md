# Tetris Game

## Introduction
This is a terminal-based implementation of the classic Tetris game in C++. It features shape stacking, collision detection, and a scoring system and also restart option providing an great  gaming experience.

## Controls  
- **Move**: `A/D` or `←/→`  
- **Rotate**: `W` or `↑`  
- **Soft Drop**: `S` or `↓`  
- **Hard Drop**: `Space`  
- **Quit**: `ESC`  

## Game Mechanics  
- Arrange falling tetrominoes to form and clear lines for points.  
- The game speeds up as lines are cleared.  
- Ends when blocks reach the top.  

## Implementation  
- **Grid**: 22×12, with `*`and  color bg as borders and cleared lines shifting down.  
- **Tetrominoes**: 7 shapes, stored as 4×4 arrays with rotation handling.  
- **Collisions**: Movement restricted by borders and existing blocks.  
- **Scoring**: `10` points per line, levels increase every `2` lines.  
- **Speed**: Starts at `500ms`, decreases with levels (min `100ms`).  
- **Graphics**: Colored console output, hidden cursor, real-time score display.
- **RNG	Mersenne Twister** (std::mt19937) seeded via chrono
- **Frame Timing**	chrono::steady_clock with millisecond precision

## Data Structures & OOPS
- **Grid:** Implemented using a 2D array to store block positions efficiently.
- **Tetrimino Representation:** Class-based structure with shape rotation logic.
- **Game Logic:** Managed in a classes for modular design and separation of functions
- **Collision Handling:** checks block positions using array indexing.
- **Dynamic Memory Usage:** Shapes are dynamically allocated and deallocated to optimize memory usage.



