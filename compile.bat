@echo off
echo ==============================================
echo  Sokoban Compilation Script (MinGW Windows)
echo ==============================================
echo 1. Graphical Mode (Default - runs game in a window)
echo 2. Console / Test Mode (No graphics - runs unit tests)
echo.
set /p choice="Enter choice (1 or 2, default is 1): "

if "%choice%"=="2" (
    echo Compiling Console / Test Mode...
    g++ -DCPORTA main.cpp coordinate.cpp gameplay.cpp graphics.cpp inputHandler.cpp level.cpp memtrace.cpp menu.cpp -o sokoban.exe
) else (
    echo Compiling Graphical Mode...
    g++ main.cpp coordinate.cpp gameplay.cpp graphics.cpp inputHandler.cpp level.cpp memtrace.cpp menu.cpp thirdparty/SDL2_gfx/SDL2_gfxPrimitives.c thirdparty/SDL2_gfx/SDL2_rotozoom.c -o sokoban.exe -Ithirdparty/SDL2/x86_64-w64-mingw32/include -Ithirdparty/SDL2/x86_64-w64-mingw32/include/SDL2 -Lthirdparty/SDL2/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows
    if %ERRORLEVEL% EQU 0 (
        echo Copying SDL2.dll...
        copy /Y "thirdparty\SDL2\x86_64-w64-mingw32\bin\SDL2.dll" "SDL2.dll" > nul
    )
)

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Compilation failed!
) else (
    echo.
    echo [SUCCESS] Compilation successful! Created sokoban.exe
)
pause
