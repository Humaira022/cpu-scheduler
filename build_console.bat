@echo off
echo ========================================
echo CPU Scheduler Console Version Build
echo ========================================
echo.

echo Building console version...
g++ -std=c++11 -O2 -o cpu_scheduler_console.exe console_main.cpp

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✓ Console version build successful!
    echo ✓ Executable created: cpu_scheduler_console.exe
    echo.
    echo Starting console application...
    cpu_scheduler_console.exe
) else (
    echo.
    echo ✗ Console build failed.
    pause
)
