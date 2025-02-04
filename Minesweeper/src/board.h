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
 * @brief The Board class
 *
 * Manages a two-dimensional grid of Cells for the Minesweeper game.
 * It handles board initialization, mine placement, adjacent mine counting,
 * cell revealing, and flag toggling.
 */
class Board
{
public:
    /**
     * @brief Board Constructs a new Board object.
     * @param rows The number of rows for the board. Default is 12.
     * @param cols The number of columns for the board. Default is 12.
     */
    Board(int rows = 12, int cols = 12);

    /**
     * @brief initialize Sets up the board by resetting cells,
     * placing mines, and calculating adjacent mine counts.
     */
    void initialize();

    /**
     * @brief checkWinCondition Determines if the game is won.
     * @return true if all non-mine cells are revealed, false otherwise.
     */
    bool checkWinCondition() const;

    /**
     * @brief getCell Returns a reference to the cell at the specified position.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @return Reference to the Cell object.
     */
    Cell& getCell(int row, int col);

    /**
     * @brief revealCell Reveals the cell at the given position and automatically reveals
     * adjacent cells if the cell has no neighboring mines.
     * @param row The row index of the cell to reveal.
     * @param col The column index of the cell to reveal.
     */
    void revealCell(int row, int col);

    /**
     * @brief toggleFlag Toggles the flagged state of the cell at the specified position.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     */
    void toggleFlag(int row, int col);

    /**
     * @brief revealBoard Reveals all cells on the board.
     */
    void revealBoard();

    /**
     * @brief rowCount Returns the number of rows in the board.
     * @return The number of rows.
     */
    int rowCount() const;

    /**
     * @brief colCount Returns the number of columns in the board.
     * @return The number of columns.
     */
    int colCount() const;

private:
    int m_rows;                         ///< Number of rows in the board.
    int m_cols;                         ///< Number of columns in the board.
    QVector<QVector<Cell>> m_cells;     ///< 2D grid of cells.

    /**
     * @brief placeMines Places mines on the board according to the provided mine string.
     * @param mines A string where each character represents whether a cell is a mine ('1') or not ('0').
     */
    void placeMines(std::string mines);

    /**
     * @brief getAdjacentCells Retrieves pointers to adjacent cells.
     * @param row The row index of the current cell.
     * @param col The column index of the current cell.
     * @return An array of pointers to adjacent Cell objects.
     */
    std::array<Cell *, 8> getAdjacentCells(int row, int col) const;

    /**
     * @brief generateMines Generates a string representing mine placement.
     * @return A string with '1's for mine cells and '0's otherwise.
     */
    std::string generateMines();

    /**
     * @brief countAdjacentMines Counts the number of mines adjacent to a given cell.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @return The count of adjacent mines.
     */
    int countAdjacentMines(int row, int col) const;
};

#endif 
