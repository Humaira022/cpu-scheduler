@echo off
echo ========================================
echo CPU Scheduler GUI - Code::Blocks Build
echo ========================================
echo.

echo Building with all required Windows libraries...
echo.

g++ -std=c++11 -O2 -mwindows -o cpu_scheduler_gui.exe gui_main.cpp -lcomctl32 -lgdi32 -luser32 -lgdiplus -lkernel32 -lshell32 -lcomdlg32 -ladvapi32 -static-libgcc -static-libstdc++

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✓ Build successful!
    echo ✓ Executable created: cpu_scheduler_gui.exe
    echo.
    echo Starting the application...
    cpu_scheduler_gui.exe
) else (
    echo.
    echo ✗ Build failed. Please check the errors above.
    echo.
    echo Common solutions:
    echo 1. Make sure MinGW-w64 is installed and in PATH
    echo 2. Verify g++ compiler is accessible
    echo 3. Check if all Windows SDK libraries are available
    echo.
    pause
)
