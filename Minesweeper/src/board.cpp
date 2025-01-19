#include "board.h"

Board::Board(int rows, int cols)
    : m_rows(rows)
    , m_cols(cols)
    , m_cells(rows, QVector<Cell>(cols))
{
}

void Board::initialize()
{
    // Reset each cell
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            m_cells[r][c].setRow(r);
            m_cells[r][c].setCol(c);
            m_cells[r][c].setIsMine(false);
            m_cells[r][c].setIsRevealed(false);
            m_cells[r][c].setAdjacentMines(0);
        }
    }

    // Place mines
    placeMines();

    // Calculate adjacency counts for all non-mine cells
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            if(!m_cells[r][c].isMine()) {
                int count = countAdjacentMines(r, c);
                m_cells[r][c].setAdjacentMines(count);
            }
        }
    }

    // The problem statement says these cells are revealed from the start:
    // (1,2) => adjacency 1
    // (2,2) => adjacency 2
    // (2,3) => adjacency 2
    // (4,4) => adjacency 1
    //
    // Those positions are given in 1-based (row,col). Convert to 0-based:
    // (1,2) -> (0,1)
    // (2,2) -> (1,1)
    // (2,3) -> (1,2)
    // (4,4) -> (3,3)
    revealCell(0, 1);
    revealCell(1, 1);
    revealCell(1, 2);
    revealCell(3, 3);

    // Optionally, if you want to EXACTLY match the stated adjacent counts (even if
    // they differ from the computed adjacency), you can override them manually:
    // m_cells[0][1].setAdjacentMines(1); // (1,2): 1
    // m_cells[1][1].setAdjacentMines(2); // (2,2): 2
    // m_cells[1][2].setAdjacentMines(2); // (2,3): 2
    // m_cells[3][3].setAdjacentMines(1); // (4,4): 1
}

void Board::placeMines()
{
    // Mines are at (1,3), (3,4), (5,1) in 1-based coordinates.
    // Convert to 0-based indices: subtract 1 from each row/col.
    // (1,3) -> (0,2)
    // (3,4) -> (2,3)
    // (5,1) -> (4,0)

    m_cells[0][2].setIsMine(true);
    m_cells[2][3].setIsMine(true);
    m_cells[4][0].setIsMine(true);
}

int Board::countAdjacentMines(int row, int col) const
{
    int count = 0;
    for(int dr = -1; dr <= 1; dr++) {
        for(int dc = -1; dc <= 1; dc++) {
            if(dr == 0 && dc == 0) 
                continue;  // skip the cell itself

            int rr = row + dr;
            int cc = col + dc;

            // Check valid boundaries
            if(rr >= 0 && rr < m_rows && cc >= 0 && cc < m_cols) {
                if(m_cells[rr][cc].isMine()) {
                    count++;
                }
            }
        }
    }
    return count;
}

Cell& Board::getCell(int row, int col)
{
    return m_cells[row][col];
}

int Board::rowCount() const
{
    return m_rows;
}

int Board::colCount() const
{
    return m_cols;
}

void Board::revealCell(int row, int col)
{
    if(row < 0 || row >= m_rows || col < 0 || col >= m_cols)
        return;
    m_cells[row][col].setIsRevealed(true);
}

void Board::toggleFlag(int row, int col)
{
    if(row < 0 || row >= m_rows || col < 0 || col >= m_cols)
        return;
    m_cells[row][col].flipFlag();
}