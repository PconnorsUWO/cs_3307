#ifndef CELL_H
#define CELL_H



/**
 * Represents a single cell in the Minesweeper board.
 */
class Cell
{
public:
    Cell();

    bool isMine() const;
    void setIsMine(bool isMine);

    bool isRevealed() const;
    void setIsRevealed(bool revealed);

    int adjacentMines() const;
    void setAdjacentMines(int count);

    bool isFlagged() const;
    void flipFlag();

    int row() const;
    void setRow(int r);

    int col() const;
    void setCol(int c);


private:
    bool m_isMine;
    bool m_isRevealed;
    bool m_isFlagged;
    int m_adjacentMines;
    int m_row;
    int m_col;

};

#endif // CELL_H
