#!/bin/bash
# ============================================
# Bash Script to Build and Run Minesweeper
# ============================================

# Choose your make tool:
MAKE_TOOL=make
# Uncomment the following line to use a different make tool (if needed)
# MAKE_TOOL=ninja

# ---------------------------
# Build and Run Section
# ---------------------------

# Change directory to the script's directory (the project root)
cd "$(dirname "$0")" || { echo "[Error] Could not change directory to script location."; exit 1; }

# Verify qmake is available
if ! command -v qmake >/dev/null 2>&1; then
    echo "[Error] qmake not found. Please ensure Qt is installed and qmake is in your PATH."
    exit 1
fi

# Verify the make tool is available
if ! command -v "$MAKE_TOOL" >/dev/null 2>&1; then
    echo "[Error] $MAKE_TOOL not found. Please ensure the make tool is installed and in your PATH."
    exit 1
fi

echo "============================================"
echo "Step 1: Running qmake to generate Makefile"
echo "============================================"
qmake Minesweeper.pro
if [ $? -ne 0 ]; then
    echo "[Error] qmake failed."
    exit 1
fi

echo "============================================"
echo "Step 2: Building the project with $MAKE_TOOL"
echo "============================================"
$MAKE_TOOL
if [ $? -ne 0 ]; then
    echo "[Error] Build failed."
    exit 1
fi

echo "============================================"
echo "Step 3: Executing Minesweeper"
echo "============================================"
# Adjust the path to the executable if it's located elsewhere.
./release/Minesweeper
