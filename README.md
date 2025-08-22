# CPU Scheduling Algorithm Simulator - Code::Blocks Project

## Overview
This is a complete Windows GUI application that simulates various CPU scheduling algorithms including:
- First Come First Serve (FCFS)
- Shortest Job First (SJF)
- Round Robin (RR)
- Priority Scheduling

## Features
- ✅ Native Windows GUI (no external libraries required)
- ✅ Interactive process input
- ✅ Real-time Gantt chart visualization
- ✅ Performance metrics calculation
- ✅ Algorithm comparison tool
- ✅ Code::Blocks project file included

## Files Included
- `gui_main.cpp` - Main source code file
- `CPU_Scheduler_GUI.cbp` - Code::Blocks project file
- `build.bat` - Quick build script
- `README.md` - This instruction file

## How to Use

### Method 1: Using Code::Blocks IDE
1. Open Code::Blocks
2. Go to File → Open → Select `CPU_Scheduler_GUI.cbp`
3. Build the project (Build → Build or press Ctrl+F9)
4. Run the executable (Build → Run or press Ctrl+F10)

### Method 2: Using Command Line
1. Open Command Prompt or PowerShell
2. Navigate to this folder
3. Run: `build.bat`
4. The application will compile and start automatically

### Method 3: Manual Compilation
```bash
g++ -std=c++11 -O2 -mwindows -o cpu_scheduler_gui.exe gui_main.cpp -lcomctl32 -lgdi32 -luser32 -lgdiplus -lkernel32 -lshell32 -lcomdlg32 -ladvapi32
```

## System Requirements
- Windows 7 or later
- MinGW-w64 compiler (usually comes with Code::Blocks)
- No additional libraries needed (uses built-in Windows API only)

## Application Usage
1. **Add Processes**: Enter arrival time, burst time, and priority for each process
2. **Select Algorithm**: Choose from FCFS, SJF, Round Robin, or Priority scheduling
3. **View Results**: See execution order, waiting times, and turnaround times
4. **Gantt Chart**: Visual representation of process execution timeline
5. **Compare Algorithms**: Run all algorithms and compare their performance

## Troubleshooting
- **Build Errors**: Ensure MinGW-w64 is properly installed and in system PATH
- **Missing Libraries**: All required libraries are built into Windows
- **GUI Issues**: Make sure you're running on Windows with GUI support

## Technical Details
- **Language**: C++11
- **GUI Framework**: Native Windows API
- **Libraries Used**: Only standard Windows libraries (user32, gdi32, comctl32, etc.)
- **Compiler**: MinGW-w64 (GCC)

## Author
GitHub Copilot - CPU Scheduling Simulator
Created: August 22, 2025
