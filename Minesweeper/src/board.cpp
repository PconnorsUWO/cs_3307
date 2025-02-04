#include "board.h"
#include <utility>

/**
 * @brief Board::Board Constructs a new Board with the specified dimensions.
 * @param rows Number of rows in the board.
 * @param cols Number of columns in the board.
 */
Board::Board(int rows, int cols)
    : m_rows(rows)
    , m_cols(cols)
    , m_cells(rows, QVector<Cell>(cols))
{
}

/**
 * @brief Board::initialize Initializes the board by resetting each cell,
 * placing mines, and calculating adjacent mine counts for non-mine cells.
 */
void Board::initialize()
{
    // Reset each cell in the board.
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            m_cells[r][c].setRow(r);
            m_cells[r][c].setCol(c);
            m_cells[r][c].setIsMine(false);
            m_cells[r][c].setIsRevealed(false);
            m_cells[r][c].setAdjacentMines(0);
        }
    }

    // Generate a string representation of mine positions and place mines.
    placeMines(generateMines());

    // Calculate and set the number of adjacent mines for each non-mine cell.
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            if (!m_cells[r][c].isMine()) {
                int count = countAdjacentMines(r, c);
                m_cells[r][c].setAdjacentMines(count);
            }
        }
    }
}

/**
 * @brief Board::generateMines Generates a string representing mine placement.
 *
 * The function calculates the number of mines based on the board size (approximately 20% of the board)
 * and randomly shuffles the mine placements.
 *
 * @return A string where '1' represents a mine and '0' represents a safe cell.
 */
std::string Board::generateMines()
{
    int BOARDLENGTH = m_rows * m_cols;
    int MINESCOUNT = BOARDLENGTH / 5;

    std::string minesStr(BOARDLENGTH, '0');

    std::vector<int> indices(BOARDLENGTH);
    for (int i = 0; i < BOARDLENGTH; ++i) {
        indices[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(indices.begin(), indices.end(), gen);

    for (int i = 0; i < MINESCOUNT; ++i) {
        minesStr[indices[i]] = '1';
    }

    return minesStr;
}

/**
 * @brief Board::placeMines Places mines on the board based on the provided string.
 * @param mines A string where each character is '1' for a mine and '0' otherwise.
 */
void Board::placeMines(std::string mines)
{
    int BOARD_SIZE = mines.length();
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (mines[i] == '1') {
            m_cells[i / m_cols][i % m_cols].setIsMine(true);
        }
    }
}

/**
 * @brief Board::checkWinCondition Checks if the win condition is met.
 *
 * The win condition is satisfied when all non-mine cells have been revealed.
 *
 * @return true if the player has won, false otherwise.
 */
bool Board::checkWinCondition() const
{
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            if (!m_cells[r][c].isMine() && !m_cells[r][c].isRevealed()) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Board::countAdjacentMines Counts the mines in adjacent cells around the specified cell.
 * @param row The row index of the current cell.
 * @param col The column index of the current cell.
 * @return The number of adjacent mines.
 */
int Board::countAdjacentMines(int row, int col) const
{
    int count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0)
                continue;  // Skip the cell itself.

            int rr = row + dr;
            int cc = col + dc;

            // Check boundaries.
            if (rr >= 0 && rr < m_rows && cc >= 0 && cc < m_cols) {
                if (m_cells[rr][cc].isMine()) {
                    count++;
                }
            }
        }
    }
    return count;
}

/**
 * @brief Board::getAdjacentCells Retrieves pointers to the eight adjacent cells.
 * @param row The row index of the current cell.
 * @param col The column index of the current cell.
 * @return An array of pointers to adjacent cells (nullptr if out-of-bounds).
 */
std::array<Cell*, 8> Board::getAdjacentCells(int row, int col) const
{
    int ROWS = m_rows;
    int COLS = m_cols;

    std::array<std::pair<int, int>, 8> DIRECTIONS = {
        std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(-1, 1),
        std::make_pair(0, -1),                          std::make_pair(0, 1),
        std::make_pair(1, -1), std::make_pair(1, 0), std::make_pair(1, 1)
    };

    // Array to store adjacent cell pointers.
    std::array<Cell*, 8> adj;
    adj.fill(nullptr);

    int currentRow = row;
    int currentCol = col;
    
    for (size_t i = 0; i < DIRECTIONS.size(); ++i) {
        int newRow = currentRow + DIRECTIONS[i].first;
        int newCol = currentCol + DIRECTIONS[i].second;
        if (newRow >= 0 && newRow < static_cast<int>(ROWS) &&
            newCol >= 0 && newCol < static_cast<int>(COLS)) {
            adj[i] = const_cast<Cell*>(&m_cells[newRow][newCol]);
        }
    }

    return adj;
}

/**
 * @brief Board::getCell Returns a reference to the cell at the specified row and column.
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @return Reference to the specified Cell.
 */
Cell& Board::getCell(int row, int col)
{
    return m_cells[row][col];
}

/**
 * @brief Board::rowCount Returns the total number of rows in the board.
 * @return The number of rows.
 */
int Board::rowCount() const
{
    return m_rows;
}

/**
 * @brief Board::colCount Returns the total number of columns in the board.
 * @return The number of columns.
 */
int Board::colCount() const
{
    return m_cols;
}

/**
 * @brief Board::revealCell Reveals the cell at (row, col) and expands to reveal adjacent cells if necessary.
 * @param row The row index of the cell to reveal.
 * @param col The column index of the cell to reveal.
 *
 * This function uses a breadth-first search (BFS) approach to reveal all connected cells
 * that have no adjacent mines. If the starting cell is a mine, it is not expanded.
 */
void Board::revealCell(int row, int col)
{
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        return;
    }
    
    // Queue for BFS traversal.
    std::queue<std::pair<int, int>> toProcess;
    toProcess.push({row, col});

    while (!toProcess.empty()) {
        auto [currentRow, currentCol] = toProcess.front();
        toProcess.pop();

        Cell &currentCell = m_cells[currentRow][currentCol];

        // Skip if the cell is already revealed or is a mine.
        if (currentCell.isRevealed() || currentCell.isMine()) {
            continue;
        }

        // Reveal the cell.
        currentCell.setIsRevealed(true);

        // If no adjacent mines, add neighbors to the queue.
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

/**
 * @brief Board::revealBoard Reveals all cells on the board.
 */
void Board::revealBoard()
{
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            m_cells[r][c].setIsRevealed(true);
        }
    }
}

/**
 * @brief Board::toggleFlag Toggles the flagged state of the cell at (row, col).
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 */
void Board::toggleFlag(int row, int col)
{
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
        return;
    m_cells[row][col].flipFlag();
}
