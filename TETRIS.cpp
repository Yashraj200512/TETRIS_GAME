#include <iostream>
#include <windows.h>
#include <conio.h>
#include <random>  // for std::mt19937 (random no. generator)
#include <chrono>  // for seeding and timing genertaor
#include <string>  //to store tetris shapes.

void setColor(int color) // for text color and boundary color.
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//  random number generator based on current time.
std::mt19937 mt{static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())};

std::uniform_int_distribution<int> tetris{0, 6};

// Tetris shapes: 7 pieces with 4 rotations each and each with 4x4 size.
const std::string tetris_shapes[7][4][4] = {
    {// I-piece
     {"    ",
      "OOOO",
      "    ",
      "    "},
     {"  O ",
      "  O ",
      "  O ",
      "  O "},
     {"    ",
      "    ",
      "OOOO",
      "    "},
     {" O  ",
      " O  ",
      " O  ",
      " O  "}},
    {// O-piece
     {"    ",
      " OO ",
      " OO ",
      "    "},
     {"    ",
      " OO ",
      " OO ",
      "    "},
     {"    ",
      " OO ",
      " OO ",
      "    "},
     {"    ",
      " OO ",
      " OO ",
      "    "}},
    {// T-piece
     {"    ",
      " O  ",
      "OOO ",
      "    "},
     {"    ",
      " O  ",
      " OO ",
      " O  "},
     {"    ",
      "    ",
      "OOO ",
      " O  "},
     {"    ",
      " O  ",
      "OO  ",
      " O  "}},
    {// S-piece
     {"    ",
      " OO ",
      "OO  ",
      "    "},
     {"    ",
      " O  ",
      " OO ",
      "  O "},
     {"    ",
      "    ",
      " OO ",
      "OO  "},
     {"    ",
      "O   ",
      "OO  ",
      " O  "}},
    {// Z-piece
     {"    ",
      "OO  ",
      " OO ",
      "    "},
     {"    ",
      "  O ",
      " OO ",
      " O  "},
     {"    ",
      "    ",
      "OO  ",
      " OO "},
     {"    ",
      " O  ",
      "OO  ",
      "O   "}},
    {// J-piece
     {"    ",
      "O   ",
      "OOO ",
      "    "},
     {"    ",
      " OO ",
      " O  ",
      " O  "},
     {"    ",
      "    ",
      "OOO ",
      "  O "},
     {"    ",
      " O  ",
      " O  ",
      "OO  "}},
    {// L-piece
     {"    ",
      "  O ",
      "OOO ",
      "    "},
     {"    ",
      " O  ",
      " O  ",
      " OO "},
     {"    ",
      "    ",
      "OOO ",
      "O   "},
     {"    ",
      "OO  ",
      " O  ",
      " O  "}}};

class tetromino // Tetromino class holds the current falling shape and its position and also has rotation function.
{
public:
    std::string shape[4];
    int x, y;
    tetromino(const std::string shapeArr[4])
    {

        for (int i = 0; i < 4; i++)
        {
            shape[i] = shapeArr[i];
        }
        // Starting position near top center.
        x = 5;
        y = 1;
    }

    void rotate(const std::string shapeArr[4]) //gets the next index of particular tetromino for rotation.
    {
        for (int i = 0; i < 4; i++)
        {
            shape[i] = shapeArr[i];
        }
    }
};

// GRID class holds the persistent grid and methods to draw and update it.
class GRID
{
    char grid[22][12];

public:
    int score;
    int level;
    int linesCleared;
    int gameSpeed;
    int Highscore;

    GRID()
    {
        initializeGrid();
        score = 0;
        level = 1;
        linesCleared = 0;
        Highscore = 0;
    }
    // Returns the character at a specified position for collision check.
    char getCell(int y, int x) const
    {
        return grid[y][x];
    }
    // Hides the console cursor.
    void hideCursor()
    {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);
    }
    // Sets the console cursor position.
    void setCursorPosition(int x, int y) const
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void placeTetromino(const tetromino &t) // Permanently locks a tetromino into the grid when it reached bottom or on top of another shape
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (t.shape[i][j] != ' ')
                {
                    grid[t.y + i][t.x + j] = t.shape[i][j];
                }
            }
        }
    }
    // Draws the grid with the falling tetromino  separate from permanent grid.
    void displayWithTetromino(const tetromino &t)
    {

        char temp[22][12]; // Create a temporary copy of grid.
        for (int i = 0; i < 22; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                temp[i][j] = grid[i][j];
            }
        }

        for (int i = 0; i < 4; i++) //  the falling tetromino.
        {
            for (int j = 0; j < 4; j++)
            {
                if (t.shape[i][j] != ' ')
                {
                    temp[t.y + i][t.x + j] = t.shape[i][j];
                }
            }
        }
        // Set the cursor at the top left.
        setCursorPosition(0, 0);

        for (int i = 0; i < 22; i++) // Display the grid.
        {
            for (int j = 0; j < 12; j++)
            {
                // If the cell is a boundary (*)
                if (temp[i][j] == '*')
                {
                    setColor(81); // Black text on purple background for boundaries.
                }
                else
                {
                    setColor(1); // blue text (on default black background) for tetromino/empty grid.
                }
                std::cout << temp[i][j] << " ";
            }

            // Print game statistics and control info on specific rows.
            if (i == 5)
            {
                setColor(12); // Red text
                std::cout << "   Score         : ";
                setColor(15); // White text for value
                std::cout << score;
            }
            if (i == 6)
            {
                setColor(12); 
                std::cout << "   High Score    : ";
                setColor(15); 
                std::cout << Highscore;
            }
            if (i == 7)
            {
                setColor(12);
                std::cout << "   Level         : ";
                setColor(15);
                std::cout << level;
            }
            if (i == 8)
            {
                setColor(12);
                std::cout << "   Lines Cleared : ";
                setColor(15);
                std::cout << linesCleared;
            }
            if (i == 10)
            {
                setColor(12);
                std::cout << "   Controls:";
            }
            if (i == 11)
            {
                setColor(12);
                std::cout << "   Game Speed    : ";
                setColor(15);
                std::cout << std::max(100, 500 - (level - 1) * 50);
            }
            if (i == 12)
            {
                setColor(12);
                std::cout << "   Movement      : ";
                setColor(15);
                std::cout << "w, a, s, d or Arrow Keys";
            }
            if (i == 13)
            {
                setColor(12);
                std::cout << "   Quit          : ";
                setColor(15);
                std::cout << "ESC";
            }

            std::cout << "\n";
        }
    }

    void initializeGrid() // Initializes grid boundaries and empty spaces.
    {
        for (int i = 0; i < 22; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                if (i == 0 || i == 21)
                {
                    grid[i][j] = '*';
                }
                else if (j == 0 || j == 11)
                {
                    grid[i][j] = '*';
                }
                else
                {
                    grid[i][j] = ' ';
                }
            }
        }
    }

    // Collision detection: checks if moving tetromino t by offsetX or offsetY causes collision.
    bool checkCollision(const tetromino &t, int offsetX, int offsetY) const
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (t.shape[i][j] != ' ')
                {
                    int newY = t.y + offsetY + i;
                    int newX = t.x + offsetX + j;
                    // Check boundaries: bottom at row 21, left at col 0, right at col 11.
                    if (newY >= 21 || newX <= 0 || newX >= 11)
                        return true;
                    // Check if the cell is already occupied.
                    if (getCell(newY, newX) != ' ')
                        return true;
                }
            }
        }
        return false;
    }

    // Processes key input for movement.
    void move(tetromino &t, int &Shape, int &shape_position)
    {
        if (kbhit())
        {
            char key = getch();
            switch (key)
            {
            case 'a':
            case 75:
            { // Left arrow
                if (!checkCollision(t, -1, 0))
                    t.x--;
                break;
            }
            case 'd':
            case 77:
            { // Right arrow
                if (!checkCollision(t, 1, 0))
                    t.x++;
                break;
            }
            case 's':
            case 80:
            { // Down arrow(soft drop)
                if (!checkCollision(t, 0, 1))
                    t.y++;
                break;
            }
            case 32:
            { // Space bar (hard drop)
                while (!checkCollision(t, 0, 1))
                    t.y++;

                placeTetromino(t); // Lock the piece into the grid

                // Spawn a new piece
                Shape = tetris(mt);
                shape_position = 0;
                t = tetromino(tetris_shapes[Shape][shape_position]);

                // Check for game over condition
                if (checkCollision(t, 0, 0))
                {
                    Gameover();
                }

                break;
            }
            case 'w':
            case 72:
            {
                int nextRotation = (shape_position + 1) % 4;
                tetromino temp(tetris_shapes[Shape][nextRotation]); // to check if rotation is causing collision
                temp.x = t.x;
                temp.y = t.y;

                if (!checkCollision(temp, 0, 0))
                {
                    shape_position = nextRotation;

                    t.rotate(tetris_shapes[Shape][shape_position]);
                }
                break;
            }
            case 27: // esc key
                exit(0);
                break;
            default:
                break;
            }
        }
    }

    void lines()
    {

        for (int i = 1; i < 21; i++)
        {
            bool isALine = true;
            for (int j = 1; j < 11; j++)
            {
                if (grid[i][j] == ' ')
                {
                    isALine = false;
                    break;
                }
            }
            if (isALine) // executes when entire row has no empty space
            {

                for (int y = i; y > 1; y--)
                {
                    for (int x = 1; x < 11; x++)
                    {
                        grid[y][x] = grid[y - 1][x]; // shifts every row downwards
                    }
                }
                for (int x = 1; x < 11; x++)
                {
                    grid[1][x] = ' ';
                }
                score += 50;
                if (Highscore < score)
                    Highscore = score;

                linesCleared++;
                if (linesCleared % 3==0)
                    level++;
                i--; // to check for same row again
            }
        }
    }

    void displayWelcomeScreen()
    {
        system("cls");
        setColor(1);
        std::cout << "\n\n";
        std::cout << "   ====================================\n";
        std::cout << "   ||                                ||\n";
        setColor(11);
        std::cout << "   ||          WELCOME TO TETRIS     ||\n";
        
        std::cout << "   ||                                ||\n";
        std::cout << "   ====================================\n\n";

        setColor(2);
        std::cout << "Controls:\n";
        setColor(13);
        std::cout << "  LEFT  : Move Left\n";
        std::cout << "  RIGHT : Move Right\n";
        std::cout << "  UP    : Rotate\n";
        std::cout << "  DOWN  : Soft Drop\n";
        std::cout << "  SPACE : Hard Drop\n";
        std::cout << "  ESC   : Quit\n\n";

        setColor(12);
        std::cout << "Press any key to start...";
        setColor(15);
        _getch();
    }

    int calculateFallInterval(int level)
    {
        return std::max(100, 500 - (level - 1) * 50); // 500 is starting speed
    }

    void runGame()
    {
        int Shape = tetris(mt); // any of the 7 shapes
        int shape_position = 0; // any of four positions,default=0.

        tetromino t(tetris_shapes[Shape][shape_position]);

        // Timer variables to control falling speed of tetromino.
        auto lastFallTime = std::chrono::steady_clock::now();

        while (true)
        {
            displayWithTetromino(t);
            move(t, Shape, shape_position); // Processes inputs from user
            lines();

            int fallInterval = calculateFallInterval(level);
            // Check if it's time for the tetromino to fall.
            auto now = std::chrono::steady_clock::now();
            int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFallTime).count();
            if (elapsed >= fallInterval)
            {
                if (checkCollision(t, 0, 1))
                {
                    // Collision: lock the tetromino.
                    placeTetromino(t);
                    Shape = tetris(mt);
                    shape_position = 0;
                    t = tetromino(tetris_shapes[Shape][shape_position]);
                    // Game over condition: if new piece collides immediately.
                    if (checkCollision(t, 0, 0))
                    {
                        Gameover();
                    }
                }
                else
                {
                    t.y++; // tetromino constantly falling down(if no collission)
                }
                lastFallTime = now;
            }
            Sleep(50); // Small sleep for smooth display and less chances of input delay .
        }
    }

    void Gameover() //game over screen display and restart function.
    {
        setCursorPosition(0, 23);
        setColor(2);
        std::cout << "   ====================================\n";
        setColor(10);
        std::cout << "   ||          GAME OVER !           ||\n";
        setColor(2);
        std::cout << "   ====================================\n\n";
        setColor(13);
        std::cout << "   ====================================\n";
        setColor(4);
        std::cout << "          your final  score: " << score << "\n";
        std::cout << "          your Highscore: " << Highscore << "\n";
        std::cout << "    press [r] to restart or esc to exit" << "\n";
        setColor(13);
        std::cout << "   ====================================\n";
        while (true)
        {
            if (kbhit()) //everything re initialized except highscore for restart.
            {
                char key = getch();
                switch (key)
                {
                case 'r':
                {
                    system("cls");

                    hideCursor();
                    initializeGrid();
                    score = 0;
                    level = 1;
                    linesCleared = 0;

                    runGame();
                    break;
                }
                case 27:  exit(0); break;
                default: std::cout<<"invalid key\n";
                   
                }
            }
            Sleep(250);
        }
    }
};

int main()
{

    GRID g;
    g.hideCursor();
    g.displayWelcomeScreen();
    system("cls");
    g.runGame();

    return 0;
}
