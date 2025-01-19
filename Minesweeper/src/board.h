#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "cell.h"

/**
 * Board manages a 2D grid of Cells. It places mines,
 * calculates adjacent mine counts, and provides
 * reveal functionality.
 */
class Board
{
public:
    Board(int rows = 10, int cols = 10);

    // Sets up the board: clears states, places mines, calculates adjacency,
    // and pre-reveals certain cells as per the requirement.
    void initialize();

    // Randomly places mines on the board
    // This is a helper function for initialize()
    void randomizeMines();

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
    void placeMines();

    // Count how many mines are adjacent to (row, col)
    int countAdjacentMines(int row, int col) const;
};

#endif // BOARD_H
