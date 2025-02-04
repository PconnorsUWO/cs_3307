#ifndef CELL_H
#define CELL_H

/**
 * @brief The Cell class
 *
 * Represents a single cell on the Minesweeper board. Each cell maintains
 * its state including whether it is a mine, if it has been revealed, whether
 * it is flagged, the number of adjacent mines, and its position on the board.
 */
class Cell
{
public:
    /**
     * @brief Cell Default constructor.
     *
     * Initializes the cell with default values:
     * - m_isMine = false
     * - m_isRevealed = false
     * - m_isFlagged (uninitialized explicitly, but typically false)
     * - m_adjacentMines = 0
     * - m_row = 0
     * - m_col = 0
     */
    Cell();

    /**
     * @brief isMine Checks if the cell contains a mine.
     * @return true if the cell is a mine, false otherwise.
     */
    bool isMine() const;

    /**
     * @brief setIsMine Sets whether the cell is a mine.
     * @param isMine true to mark the cell as a mine, false otherwise.
     */
    void setIsMine(bool isMine);

    /**
     * @brief isRevealed Checks if the cell has been revealed.
     * @return true if revealed, false otherwise.
     */
    bool isRevealed() const;

    /**
     * @brief setIsRevealed Sets the cell's revealed status.
     * @param revealed true if the cell is revealed, false otherwise.
     */
    void setIsRevealed(bool revealed);

    /**
     * @brief adjacentMines Returns the number of mines adjacent to this cell.
     * @return The count of adjacent mines.
     */
    int adjacentMines() const;

    /**
     * @brief setAdjacentMines Sets the number of adjacent mines.
     * @param count The count to set.
     */
    void setAdjacentMines(int count);

    /**
     * @brief isFlagged Checks if the cell is flagged.
     * @return true if flagged, false otherwise.
     */
    bool isFlagged() const;

    /**
     * @brief flipFlag Toggles the flagged state of the cell.
     *
     * If the cell is flagged, it becomes unflagged, and vice versa.
     */
    void flipFlag();

    /**
     * @brief row Returns the row index of the cell.
     * @return The row index.
     */
    int row() const;

    /**
     * @brief setRow Sets the row index of the cell.
     * @param r The row index.
     */
    void setRow(int r);

    /**
     * @brief col Returns the column index of the cell.
     * @return The column index.
     */
    int col() const;

    /**
     * @brief setCol Sets the column index of the cell.
     * @param c The column index.
     */
    void setCol(int c);

private:
    bool m_isMine;          ///< Indicates if this cell is a mine.
    bool m_isRevealed;      ///< Indicates if this cell has been revealed.
    bool m_isFlagged;       ///< Indicates if this cell is flagged.
    int m_adjacentMines;    ///< Number of adjacent mines.
    int m_row;              ///< Row position of the cell.
    int m_col;              ///< Column position of the cell.
};

#endif // CELL_H
