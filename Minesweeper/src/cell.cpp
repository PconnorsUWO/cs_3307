#include "cell.h"

/**
 * @brief Cell::Cell Default constructor.
 *
 * Initializes the cell with default values:
 * - Not a mine.
 * - Not revealed.
 * - 0 adjacent mines.
 * - Position (0, 0).
 */
Cell::Cell()
    : m_isMine(false)
    , m_isRevealed(false)
    , m_adjacentMines(0)
    , m_row(0)
    , m_col(0)
{
}

/**
 * @brief Cell::isMine Checks if the cell is a mine.
 * @return true if the cell contains a mine.
 */
bool Cell::isMine() const
{
    return m_isMine;
}

/**
 * @brief Cell::setIsMine Sets the mine status of the cell.
 * @param isMine true if this cell should be marked as a mine.
 */
void Cell::setIsMine(bool isMine)
{
    m_isMine = isMine;
}

/**
 * @brief Cell::isRevealed Checks if the cell has been revealed.
 * @return true if the cell is revealed.
 */
bool Cell::isRevealed() const
{
    return m_isRevealed;
}

/**
 * @brief Cell::setIsRevealed Sets the revealed status of the cell.
 * @param revealed true to mark the cell as revealed.
 */
void Cell::setIsRevealed(bool revealed)
{
    m_isRevealed = revealed;
}

/**
 * @brief Cell::isFlagged Checks if the cell is flagged.
 * @return true if the cell is flagged.
 */
bool Cell::isFlagged() const
{
    return m_isFlagged;
}

/**
 * @brief Cell::flipFlag Toggles the flagged status of the cell.
 *
 * If the cell is flagged, this function will unflag it, and vice versa.
 */
void Cell::flipFlag()
{
    m_isFlagged = !m_isFlagged;
}

/**
 * @brief Cell::adjacentMines Returns the number of adjacent mines.
 * @return The count of adjacent mines.
 */
int Cell::adjacentMines() const
{
    return m_adjacentMines;
}

/**
 * @brief Cell::setAdjacentMines Sets the number of adjacent mines.
 * @param count The number of mines adjacent to this cell.
 */
void Cell::setAdjacentMines(int count)
{
    m_adjacentMines = count;
}

/**
 * @brief Cell::row Returns the row index of the cell.
 * @return The row index.
 */
int Cell::row() const
{
    return m_row;
}

/**
 * @brief Cell::setRow Sets the row index for the cell.
 * @param r The row index to set.
 */
void Cell::setRow(int r)
{
    m_row = r;
}

/**
 * @brief Cell::col Returns the column index of the cell.
 * @return The column index.
 */
int Cell::col() const
{
    return m_col;
}

/**
 * @brief Cell::setCol Sets the column index for the cell.
 * @param c The column index to set.
 */
void Cell::setCol(int c)
{
    m_col = c;
}
