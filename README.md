# Sokoban in C++

A portable implementation of the classic Sokoban puzzle game written in C++ using **SDL2** and **SDL2_gfx** for rendering.

The project is structured to be completely self-contained for Windows users, meaning you can compile and run it immediately without manually installing any graphics libraries.

---

## Game Rules & Objective

Sokoban is a classic transport puzzle game.
1. The player is represented by a **red circle** (`@`).
2. The crates/boxes are represented by **brown squares** (`$`).
3. The targets/storage locations are represented by **green circles** (`.`).
4. **Your goal** is to push all boxes onto the green storage targets. 
5. When a box is successfully pushed onto a target, the target fills up (`*`).
6. You can only **push** boxes, you cannot **pull** them, and you can only push one box at a time. Be careful not to push them into corners!

---

## Game Controls

### Main Menu Navigation
When the game starts, you will see a grid of grey circles representing the available levels.
- **Navigate Selection**: `W` (Up), `A` (Left), `S` (Down), `D` (Right)
- **Select / Load Level**: `Space` or `Enter`
- **Quit Game**: `Q` or `Escape`

### During Gameplay
- **Movement**: `W` (Up), `A` (Left), `S` (Down), `D` (Right)
- **Undo Last Move**: `E` or `U` (allows you to backtrack steps if you make a mistake)
- **Exit to Main Menu**: `Q` or `Escape`

---

## Directory Structure

```
├── levels/                # Level design text files (soko001.txt, etc.)
├── thirdparty/            # Portable libraries (Windows MinGW 64-bit)
│   ├── SDL2/              # Official SDL2 development library
│   └── SDL2_gfx/          # SDL2_gfx source code (compiled directly with the project)
├── compile.bat            # One-click interactive compilation script for Windows
├── .gitignore             # Keeps repository clean of compiled binaries and local files
└── [source files]         # C++ source (.cpp) and header (.h) files
```

---

## How to Compile & Run

### Windows (MSYS2 / MinGW-w64)

The repository includes a portable, pre-configured compilation script.

1. Double-click `compile.bat` (or run it in Command Prompt/PowerShell).
2. Choose either **Graphical Mode** (Option 1) or **Console Mode** (Option 2).
3. The script will automatically compile the project and copy the necessary `SDL2.dll` to the root folder.
4. Run the game:
   ```bash
   .\sokoban.exe
   ```

### Linux (Ubuntu/Debian)

1. Install SDL2 and SDL2_gfx development packages:
   ```bash
   sudo apt update
   sudo apt install libsdl2-dev libsdl2-gfx-dev
   ```
2. Compile the project:
   ```bash
   g++ main.cpp coordinate.cpp gameplay.cpp graphics.cpp inputHandler.cpp level.cpp memtrace.cpp menu.cpp thirdparty/SDL2_gfx/SDL2_gfxPrimitives.c thirdparty/SDL2_gfx/SDL2_rotozoom.c -o sokoban -Ithirdparty/SDL2_gfx `sdl2-config --cflags --libs`
   ```
3. Run the game:
   ```bash
   ./sokoban
   ```

### macOS

1. Install SDL2 and SDL2_gfx via Homebrew:
   ```bash
   brew install sdl2 sdl2_gfx
   ```
2. Compile the project:
   ```bash
   g++ main.cpp coordinate.cpp gameplay.cpp graphics.cpp inputHandler.cpp level.cpp memtrace.cpp menu.cpp thirdparty/SDL2_gfx/SDL2_gfxPrimitives.c thirdparty/SDL2_gfx/SDL2_rotozoom.c -o sokoban -Ithirdparty/SDL2_gfx `sdl2-config --cflags --libs`
   ```
3. Run the game:
   ```bash
   ./sokoban
   ```

---

## Running Unit Tests (Console Mode)

To run the automated test suite, compile the project in Console Mode (Option 2 in `compile.bat` or by passing `-DCPORTA` to the compiler). 

Before running, make sure the test runner can locate the test maps:
1. Copy `levels/soko002.txt` to the root folder as `soko001.txt`.
2. Copy `levels/soko007.txt` to the root folder as `cportatest.txt` (or create a custom layout).
3. Run `sokoban.exe` or redirect test inputs:
   ```bash
   Get-Content input.txt | .\sokoban.exe
   ```
