# Tetris
# Tetris Game in C++

## Overview
This is a simple console-based Tetris game built using C++. It utilizes Windows API functions for console manipulation, such as setting text colors, moving the cursor, and playing background music.

## Features
- **Classic Tetris gameplay** with falling blocks and rotation
- **Ghost piece preview** to show where the current piece will land
- **Scoring system** with high score tracking
- **Background music support** using `PlaySound()`
- **Keyboard controls** for movement, rotation, and restarting the game
- **Windows console-based rendering** for smooth animation

## Requirements
- Windows OS (since it uses Windows-specific APIs like `PlaySound`, `SetConsoleTextAttribute`, etc.)
- C++ Compiler (MinGW, MSVC, or any other that supports Windows API functions)
- A compatible `.wav` file for background music (e.g., `ganna.wav` in the same directory as the executable)

## Installation & Compilation
### 1. Clone the repository
```sh
 git clone https://github.com/yourusername/tetris-cpp.git
 cd tetris-cpp
```

### 2. Compile the program
Using MinGW:
```sh
g++ tetris.cpp -o tetris.exe -lwinmm
```
Or using MSVC:
```sh
cl tetris.cpp /Fe:tetris.exe /link winmm.lib
```

### 3. Run the game
```sh
tetris.exe
```

## Controls
- **A / D** → Move piece left / right
- **S** → Move piece down
- **Space** → Drop piece instantly
- **Z / X** → Rotate piece left / right
- **R** → Restart game
- **M** → Toggle background music
- **ESC** → Exit game

## Troubleshooting
### **Music not playing?**
- Ensure `ganna.wav` is in the same directory as `tetris.exe`
- The `.wav` file should be in **PCM format**
- Try replacing `PlaySound()` with `mciSendString()` (see alternative implementation in comments)

### **Game crashes or visual glitches?**
- Run the program in **Windows CMD**, not in an IDE terminal
- Use a **console window size of at least 22x25** (set automatically in the code)
- Try running as Administrator if the console window is not resizing properly

## Future Improvements
- Adding an **AI opponent** or multiplayer mode
- Implementing **soft drop and hold piece mechanics**
- Supporting **customizable key bindings**
- Cross-platform support for Linux & macOS (replace Windows-specific APIs)

## License
This project is open-source and available under the **MIT License**.

## Author
Developed by **[Your Name]**

---
Happy coding! 🎮

