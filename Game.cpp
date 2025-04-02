#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

// Piece colors (using Windows console colors)
const int COLORS[] = {
    9,  // I (blue)
    11, // J (light blue)
    14, // L (yellow)
    12, // O (red)
    10, // S (green)
    13, // T (purple)
    2   // Z (dark green)
};

class Piece {
public:
    vector<vector<int>> shape;
    int size;
    int color;
    
    Piece(vector<vector<int>> s, int c) : shape(s), size(s.size()), color(c) {}
    
    void rotateRight() {
        vector<vector<int>> rotated(size, vector<int>(size));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                rotated[j][size-1-i] = shape[i][j];
            }
        }
        shape = rotated;
    }

    void rotateLeft() {
        vector<vector<int>> rotated(size, vector<int>(size));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                rotated[size-1-j][i] = shape[i][j];
            }
        }
        shape = rotated;
    }
};

class TetrisGame {
private:
    const int WIDTH = 10;
    const int HEIGHT = 20;
    vector<vector<int>> board;
    vector<vector<int>> boardColors;
    Piece* current;
    int x, y;
    int score;
    int highScore = 0;
    vector<Piece> pieces;
    HANDLE console;
    bool firstRun;
    bool musicEnabled;

    // Play background music
    void playMusic() {
        if (musicEnabled) {
            PlaySound(TEXT("ganna.wav"), NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
        }
    }

    // Stop background music
    void stopMusic() {
        PlaySound(NULL, NULL, 0);
    }

    // Set console text color
    void setColor(int color) {
        SetConsoleTextAttribute(console, color);
    }

    // Move cursor to position
    void gotoXY(int x, int y) {
        COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
        SetConsoleCursorPosition(console, coord);
    }

    // Clear only the game area
    void clearGameArea() {
        setColor(7); // White
        for (int i = 0; i < HEIGHT; i++) {
            gotoXY(0, i);
            for (int j = 0; j < WIDTH; j++) {
                cout << "  ";
            }
        }
    }

    // Clear the entire screen
    void clearFullScreen() {
        system("cls");
    }

public:
    TetrisGame() : console(GetStdHandle(STD_OUTPUT_HANDLE)), firstRun(true), musicEnabled(true) {
        // Clear screen on first run
        clearFullScreen();
        
        // Start background music
        playMusic();
        
        // Define all Tetris pieces
        pieces = {
            Piece({ // I
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0},
                {0,0,0,0}
            }, COLORS[0]),
            Piece({ // J
                {1,0,0},
                {1,1,1},
                {0,0,0}
            }, COLORS[1]),
            Piece({ // L
                {0,0,1},
                {1,1,1},
                {0,0,0}
            }, COLORS[2]),
            Piece({ // O
                {1,1},
                {1,1}
            }, COLORS[3]),
            Piece({ // S
                {0,1,1},
                {1,1,0},
                {0,0,0}
            }, COLORS[4]),
            Piece({ // T
                {0,1,0},
                {1,1,1},
                {0,0,0}
            }, COLORS[5]),
            Piece({ // Z
                {1,1,0},
                {0,1,1},
                {0,0,0}
            }, COLORS[6])
        };
        
        resetGame();
        firstRun = false;
    }

    ~TetrisGame() {
        // Stop music when game ends
        stopMusic();
    }

    void resetGame() {
        board = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
        boardColors = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 7));
        score = 0;  // Reset current score
        // Don't reset highScore here - it should persist
        spawnPiece();
        draw();  // Explicitly redraw to prevent visual glitches
    }

    void spawnPiece() {
        current = new Piece(pieces[rand() % pieces.size()]);
        x = WIDTH/2 - current->size/2;
        y = 0;
        
        if (!canMove(0, 0)) {
            gameOver();
        }
    }

    bool canMove(int dx, int dy) {
        for (int i = 0; i < current->size; i++) {
            for (int j = 0; j < current->size; j++) {
                if (current->shape[i][j]) {
                    int newX = x + j + dx;
                    int newY = y + i + dy;
                    
                    if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || 
                        (newY >= 0 && board[newY][newX])) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void lockPiece() {
        for (int i = 0; i < current->size; i++) {
            for (int j = 0; j < current->size; j++) {
                if (current->shape[i][j] && y+i >= 0) {
                    board[y+i][x+j] = 1;
                    boardColors[y+i][x+j] = current->color;
                }
            }
        }
        delete current;
        clearLines();
        spawnPiece();
    }
    
    void calculateGhostPosition(int& ghostY) {
        ghostY = y;
        while (canMove(0, ghostY - y + 1)) {
            ghostY++;
        }
    }

    void clearLines() {
        int linesCleared = 0;
        
        for (int i = HEIGHT-1; i >= 0; i--) {
            bool full = true;
            for (int j = 0; j < WIDTH; j++) {
                if (!board[i][j]) {
                    full = false;
                    break;
                }
            }
            
            if (full) {
                board.erase(board.begin() + i);
                boardColors.erase(boardColors.begin() + i);
                board.insert(board.begin(), vector<int>(WIDTH, 0));
                boardColors.insert(boardColors.begin(), vector<int>(WIDTH, 7));
                linesCleared++;
                i++; // Check same line again
            }
        }
        
        if (linesCleared > 0) {
            score += linesCleared * 100;
            if (score > highScore) highScore = score;
        }
    }

    void gameOver() {
        clearFullScreen();
        setColor(12); // Red
        cout << " GAME OVER!\n";
        setColor(7); // White
        cout << " Score: " << score << "\n";
        cout << " High Score: " << highScore << "\n\n";
        cout << " Press any key to restart\n";
        cout << " ESC to exit\n";
        cout << " M to toggle music\n";
        
        if (_getch() == 27) exit(0);
        resetGame();
    }

    void draw() {
        if (!firstRun) {
            clearGameArea();
        }
        
        // Draw the board
        for (int i = 0; i < HEIGHT; i++) {
            gotoXY(0, i);
            for (int j = 0; j < WIDTH; j++) {
                if (board[i][j]) {
                    setColor(boardColors[i][j]);
                    cout << "[]";
                } else {
                    setColor(8); // Gray
                    cout << " .";
                }
            }
        }
        
        // Calculate and draw ghost piece
        int ghostY;
        calculateGhostPosition(ghostY);
        for (int i = 0; i < current->size; i++) {
            for (int j = 0; j < current->size; j++) {
                if (current->shape[i][j] && ghostY+i >= 0) {
                    gotoXY((x+j)*2, ghostY+i);
                    setColor(8); // Gray color for ghost
                    cout << "::"; // Different character for ghost
                }
            }
        }
        
        // Draw current piece
        for (int i = 0; i < current->size; i++) {
            for (int j = 0; j < current->size; j++) {
                if (current->shape[i][j] && y+i >= 0) {
                    gotoXY((x+j)*2, y+i);
                    setColor(current->color);
                    cout << "[]";
                }
            }
        }
        
        // Draw score and controls
        setColor(15);
        gotoXY(0, HEIGHT);
        cout << "Score: " << score << "  Highscore: " << highScore;
        
        gotoXY(0, HEIGHT+1);
        cout << "Controls: A/D=Left/Right S=Down";
        gotoXY(0, HEIGHT+2);
        cout << "Z/X=Rotate Space=Drop R=Restart";
        gotoXY(0, HEIGHT+3);
        cout << "M=Toggle Music ESC=Exit";
    }

    void run() {
        // Hide cursor
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(console, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(console, &cursorInfo);
        
        // Set up timer
        clock_t lastFall = clock();
        int fallSpeed = 500; // milliseconds
        
        // Initial draw
        draw();
        
        while (true) {
            // Handle input
            if (_kbhit()) {
                char key = _getch();
                switch (key) {
                    case 'a': 
                        if (canMove(-1, 0)) x--; 
                        break;
                    case 'd': 
                        if (canMove(1, 0)) x++; 
                        break;
                    case 's': 
                        if (canMove(0, 1)) y++; 
                        break;
                    case ' ': 
                        while (canMove(0, 1)) y++; 
                        lockPiece();
                        break;
                    case 'x': 
                        current->rotateRight(); 
                        if (!canMove(0, 0)) current->rotateLeft();
                        break;
                    case 'z': 
                        current->rotateLeft(); 
                        if (!canMove(0, 0)) current->rotateRight();
                        break;
                    case 'r': 
                        resetGame();
                        clearFullScreen();
                        draw();
                        break;
                    case 'm':
                        musicEnabled = !musicEnabled;
                        if (musicEnabled) playMusic();
                        else stopMusic();
                        break;
                    case 27: 
                        system("cls");
                        cout << "Thank you for playing!";
                        return; // ESC to exit
                }
                draw();
            }
            
            // Automatic falling
            if (clock() - lastFall > fallSpeed) {
                if (canMove(0, 1)) {
                    y++;
                } else {
                    lockPiece();
                }
                draw();
                lastFall = clock();
            }
            
            Sleep(100);
        }
    }
};

int main() {
    // Set console window size
    system("mode con: cols=22 lines=25");
    
    // Disable window resizing
    HWND console = GetConsoleWindow();
    SetWindowLong(console, GWL_STYLE, 
        GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    
    srand(time(0));
    TetrisGame game;
    game.run();
    return 0;
}