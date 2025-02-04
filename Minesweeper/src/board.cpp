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

    placeMines(generateMines());

    // Calculate adjacency counts for all non-mine cells
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            if(!m_cells[r][c].isMine()) {
                int count = countAdjacentMines(r, c);
                m_cells[r][c].setAdjacentMines(count);
            }
        }
    }

}

std::string Board::generateMines()
{
    int BOARDLENGTH = m_rows * m_cols;
    int MINESCOUNT = BOARDLENGTH / 5; 

    std::string minesStr(BOARDLENGTH, '0');

    std::vector<int> indices(BOARDLENGTH);
    for(int i = 0; i < BOARDLENGTH; ++i) {
        indices[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(indices.begin(), indices.end(), gen);

    for(int i = 0; i < MINESCOUNT; ++i) {
        minesStr[indices[i]] = '1';
    }

    return minesStr;
}


void Board::placeMines(std:: string mines)
{
    int BOARD_SIZE = mines.length();
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (mines[i] == '1')
        {
            m_cells[i / m_cols][i % m_cols].setIsMine(true);
        }
    }
}


bool Board::checkWinCondition() const
{
    // Check if all non-mine cells are revealed
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            if(!m_cells[r][c].isMine() && !m_cells[r][c].isRevealed()) {
                return false;
            }
        }
    }
    return true;
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

std::array<Cell *, 8> Board::getAdjacentCells(int row, int col) const
{
    int ROWS = m_rows;
    int COLS = m_cols;

    std::array<std::pair<int, int>, 8> DIRECTIONS = {
        std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(-1, 1),
        std::make_pair(0, -1),                          std::make_pair(0, 1),
        std::make_pair(1, -1), std::make_pair(1, 0), std::make_pair(1, 1)
    };

    // Create an array to store pointers to adjacent cells
    std::array<Cell*, 8> adj;
    adj.fill(nullptr);

    // Get the current cell's position
    int currentRow = row;
    int currentCol = col;
    
    for (size_t i = 0; i < DIRECTIONS.size(); ++i) {
        int newRow = currentRow + DIRECTIONS[i].first;
        int newCol = currentCol + DIRECTIONS[i].second;

        // Check if the new position is within grid bounds
        if (newRow >= 0 && newRow < static_cast<int>(ROWS) &&
            newCol >= 0 && newCol < static_cast<int>(COLS)) {
            adj[i] = const_cast<Cell*>(&m_cells[newRow][newCol]);
        }
    }

    return adj;
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
    // Check boundaries and avoid invalid input
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        return;
    }
    
    // Queue for cells to process
    std::queue<std::pair<int, int>> toProcess;
    toProcess.push({row, col});

    while (!toProcess.empty()) {
        auto [currentRow, currentCol] = toProcess.front();
        toProcess.pop();

        Cell &currentCell = m_cells[currentRow][currentCol];

        // Skip if already revealed or if it's a mine
        if (currentCell.isRevealed() || currentCell.isMine()) {
            continue;
        }

        // Reveal the current cell
        currentCell.setIsRevealed(true);

        // If the cell has no adjacent mines, add its neighbors to the queue
        if (currentCell.adjacentMines() == 0) {
            std::array<Cell *, 8> adj = getAdjacentCells(currentRow, currentCol);
            for (Cell *neighbor : adj) {
                if (neighbor && !neighbor->isRevealed() && !neighbor->isMine()) {
                    int neighborRow = neighbor->row();
                    int neighborCol = neighbor->col();
                    toProcess.push({neighborRow, neighborCol});
                }
            }
        }
    }

    m_cells[row][col].setIsRevealed(true);
}

void Board::toggleFlag(int row, int col)
{
    if(row < 0 || row >= m_rows || col < 0 || col >= m_cols)
        return;
    m_cells[row][col].flipFlag();
}