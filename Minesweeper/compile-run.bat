@echo off
REM ============================================
REM Batch Script to Build and Run Minesweeper
REM ============================================

REM Enable command echoing for debugging (optional)
REM @echo on

REM ---------------------------
REM Configuration Section
REM ---------------------------

REM Specify the Qt version's qmake path if not in PATH
REM Example for Qt installed in C:\Qt\5.15.2\mingw81_64\bin
REM set QMAKE_PATH=C:\Qt\5.15.2\mingw81_64\bin
REM set PATH=%QMAKE_PATH%;%PATH%

REM Choose your make tool: uncomment one of the following
set MAKE_TOOL=make
REM set MAKE_TOOL=nmake

REM ---------------------------
REM Build and Run Section
REM ---------------------------

REM Navigate to the script's directory (project root)
cd /d "%~dp0"

REM Verify qmake is available
where qmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [Error] qmake not found. Please ensure Qt is installed and qmake is in your PATH.
    pause
    exit /b 1
)

REM Verify the make tool is available
where %MAKE_TOOL% >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [Error] %MAKE_TOOL% not found. Please ensure the make tool is installed and in your PATH.
    pause
    exit /b 1
)

echo ============================================
echo Step 1: Running qmake to generate Makefile
echo ============================================
qmake Minesweeper.pro
if %ERRORLEVEL% NEQ 0 (
    echo [Error] qmake failed.
    pause
    exit /b 1
)

echo ============================================
echo Step 2: Building the project with %MAKE_TOOL%
echo ============================================
%MAKE_TOOL%
if %ERRORLEVEL% NEQ 0 (
    echo [Error] Build failed.
    pause
    exit /b 1
)

echo ============================================
echo Step 3: Executing Minesweeper.exe
echo ============================================
REM Adjust the path to Minesweeper.exe if it's located elsewhere
release\Minesweeper.exe
