
# Minesweeper Project

This repository contains the implementation of the Minesweeper game using Qt. The project is structured as follows:

## Directory Structure

```
├── Individual Assignment-2025.docx   # The assignment document outlining the project requirements.
├── Minesweeper                       # Main directory for the Minesweeper project.
│   ├── Minesweeper.pro               # Qt project file for building the application.
│   ├── README.md                     # README specific to the Minesweeper project.
│   └── src                           # Source files for the Minesweeper application.
│       ├── board.cpp                 # Implementation of the game board logic.
│       ├── cell.cpp                  # Implementation of individual cell behavior and state.
│       ├── main.cpp                  # Entry point of the application.
│       └── mainwindow.cpp            # Implementation of the main game window interface.
└── README.md                         # This file, providing an overview of the repository structure.
```

## Description

- **Individual Assignment-2025.docx**: Contains the detailed instructions and requirements for the Minesweeper assignment.
- **Minesweeper.pro**: The Qt project file used to configure and build the application using `qmake` and `make`.
- **README.md (in Minesweeper)**: Specific instructions, usage details, and additional notes for the Minesweeper application.
- **src**: Contains all source code for the Minesweeper application:
  - `board.cpp`: Manages the game board, including mine placement and adjacent mine calculations.
  - `cell.cpp`: Handles the behavior and state of individual cells (e.g., opened, marked, mine detection).
  - `main.cpp`: The main entry point for starting the application.
  - `mainwindow.cpp`: Implements the main game interface, integrating the board and cell logic with the GUI.

## Building and Running the Application

1. **Requirements**:
   - Qt 5.x installed on your system.
   - A C++ compiler compatible with Qt.

2. **Steps to Build**:
   - Navigate to the `Minesweeper` directory.
   - Run `qmake` to generate the Makefile:
     ```bash
     qmake Minesweeper.pro
     ```
   - Compile the application using `make`:
     ```bash
     make
     ```

3. **Run the Application**:
   - Execute the generated binary to start the game:
     ```bash
     ./Minesweeper
     ```

## Additional Notes

- This project adheres to the coding guidelines specified in the assignment.
- For any issues or questions, refer to the `Individual Assignment-2025.docx` file for details or contact the project maintainer.
