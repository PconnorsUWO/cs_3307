#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "cell.h"
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <queue>

/**
 * Board manages a 2D grid of Cells. It places mines,
 * calculates adjacent mine counts, and provides
 * reveal functionality.
 */
class Board
{
public:
    Board(int rows = 5, int cols = 5);

    // Sets up the board: clears states, places mines, calculates adjacency,
    // and pre-reveals certain cells as per the requirement.
    void initialize();

    // Checks if the player has won the game
    bool checkWinCondition() const;

    // Access a specific cell by row/col index
    Cell& getCell(int row, int col);

    // Reveal a cell (mark as revealed in the data structure)
    void revealCell(int row, int col);

    // Mark a cell with a flag (mark as flagged in the data structure)
    void toggleFlag(int row, int col);

    // Basic getters
    int rowCount() const;
    int colCount() const;



private:
    int m_rows;
    int m_cols;
    QVector<QVector<Cell>> m_cells;

    // Places mines in the required positions
    void placeMines(std:: string mines);

    // Returns a array of pointers to the 8 adjacent cells
    std::array<Cell *, 8> getAdjacentCells (int row, int col) const;

    // Generates a binary string of mines for a new valid board
    std::string generateMines();

    // Count how many mines are adjacent to (row, col)
    int countAdjacentMines(int row, int col) const;
};

#endif // BOARD_H
