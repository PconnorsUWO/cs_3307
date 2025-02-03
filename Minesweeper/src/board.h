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


    void initialize();

    bool checkWinCondition() const;

    Cell& getCell(int row, int col);

    void revealCell(int row, int col);

    void toggleFlag(int row, int col);

    int rowCount() const;
    int colCount() const;



private:
    int m_rows;
    int m_cols;
    QVector<QVector<Cell>> m_cells;

    void placeMines(std:: string mines);

    std::array<Cell *, 8> getAdjacentCells (int row, int col) const;

    std::string generateMines();

    int countAdjacentMines(int row, int col) const;
};

#endif 
