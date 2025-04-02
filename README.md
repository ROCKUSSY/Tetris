# Tetris Game in C++

## Overview
This is a console-based Tetris game implemented in C++ using the Windows API for console manipulation. It features a classic Tetris experience with various block shapes, smooth controls, a ghost piece for better visibility, and background music.

## Features
- **Classic Tetris Gameplay**: Standard 10x20 grid with different shaped blocks.
- **Piece Rotation**: Rotate pieces left ('Z') and right ('X').
- **Ghost Piece**: Shows where the current piece will land.
- **Scoring System**: Gain points for clearing lines.
- **High Score Tracking**: Persistent high score display.
- **Music Playback**: Background music can be toggled on/off.
- **Soft & Hard Drop**: Move pieces down manually or instantly drop them.
- **User-Friendly Controls**:
  - `A/D` to move left/right
  - `S` to move down
  - `Z/X` to rotate
  - `Space` to hard drop
  - `R` to restart
  - `M` to toggle music
  - `ESC` to exit
- **Windows Console UI**: Utilizes colors for different pieces and dynamically updates the screen.

## Installation and Running the Game
1. Ensure you have a Windows machine with a C++ compiler (MinGW or MSVC).
2. Clone or download the repository.
3. Compile the code using:
   ```bash
   g++ tetris.cpp -o tetris -lwinmm
   ```
4. Run the executable:
   ```bash
   tetris.exe
   ```

## Screenshots
![WhatsApp Image 2025-04-02 at 16 22 15_8e527442](https://github.com/user-attachments/assets/6821fb43-d519-4573-b0b1-2ec7ab2c7cde)

![WhatsApp Image 2025-04-02 at 16 24 04_3a107330](https://github.com/user-attachments/assets/fe160028-254c-472d-a297-dd99190415fe)

## Author
**The Generals**

## Notes
- The game uses `windows.h` and `mmsystem.h`, making it Windows-exclusive.
- Background music file (`ganna.wav`) should be in the same directory.
- The console size is set to 22 columns by 25 lines for optimal display.

