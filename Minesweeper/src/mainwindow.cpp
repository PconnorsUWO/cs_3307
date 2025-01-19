#include "mainwindow.h"
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox> // For displaying messages (if needed)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Initialize the board (place mines, set adjacency, reveal some cells, etc.)
    m_board.initialize();

    // Create a central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a grid layout to hold the buttons
    QGridLayout *layout = new QGridLayout(centralWidget);
    centralWidget->setLayout(layout);

    // Resize our button container and place a QRightClickButton for each cell
    m_buttons.resize(m_board.rowCount());
    for(int r = 0; r < m_board.rowCount(); r++) {
        m_buttons[r].resize(m_board.colCount());
        for(int c = 0; c < m_board.colCount(); c++) {
            QRightClickButton *btn = new QRightClickButton(this);
            btn->setFixedSize(40, 40); // Optional size preference
            layout->addWidget(btn, r, c);
            m_buttons[r][c] = btn;

            // Connect left-click (clicked()) to handleCellClick
            connect(btn, &QPushButton::clicked, this, &MainWindow::handleCellClick);

            // Connect right-click (rightClicked()) to handleCellRightClick
            connect(btn, &QRightClickButton::rightClicked, this, &MainWindow::handleCellRightClick);
        }
    }

    // Initial render
    updateBoardDisplay();
}

MainWindow::~MainWindow()
{
    // Properly delete buttons if not using parent-child hierarchy
    // Qt's parent-child system should handle deletion if set up correctly
}

void MainWindow::handleCellClick()
{
    // Identify which button was clicked
    QRightClickButton *clickedButton = qobject_cast<QRightClickButton*>(sender());
    if(!clickedButton) return;

    // Find row and column of the clicked button
    int clickedRow = -1;
    int clickedCol = -1;
    for(int r = 0; r < m_board.rowCount(); r++) {
        for(int c = 0; c < m_board.colCount(); c++) {
            if(m_buttons[r][c] == clickedButton) {
                clickedRow = r;
                clickedCol = c;
                break;
            }
        }
        if(clickedRow != -1) break;
    }

    if(clickedRow == -1 || clickedCol == -1) {
        qWarning() << "Clicked button not found in the grid.";
        return;
    }

    
    // Reveal the cell in the Board data structure
    m_board.revealCell(clickedRow, clickedCol);

    // Update the GUI to reflect the change

    // Check for game over conditions (e.g., clicked on a mine)
    if(m_board.getCell(clickedRow, clickedCol).isMine()) {
        QMessageBox::information(this, "Game Over", "You clicked on a mine!");
    }
    
    if(m_board.checkWinCondition()) {
        QMessageBox::information(this, "Game Over", "You won!");
    }

    updateBoardDisplay();

    // Check for win condition if applicable
    // if(m_board.checkWinCondition()) { /* Handle win */ }
}

void MainWindow::handleCellRightClick()
{
    // Identify which button was right-clicked
    QRightClickButton *clickedButton = qobject_cast<QRightClickButton*>(sender());
    if(!clickedButton) return;

    // Find row and column of the clicked button
    int clickedRow = -1;
    int clickedCol = -1;
    for(int r = 0; r < m_board.rowCount(); r++) {
        for(int c = 0; c < m_board.colCount(); c++) {
            if(m_buttons[r][c] == clickedButton) {
                clickedRow = r;
                clickedCol = c;
                break;
            }
        }
        if(clickedRow != -1) break;
    }

    if(clickedRow == -1 || clickedCol == -1) {
        qWarning() << "Right-clicked button not found in the grid.";
        return;
    }

    // Toggle flag on the cell in the Board data structure
    m_board.toggleFlag(clickedRow, clickedCol);

    // Update the GUI to reflect the change
    updateBoardDisplay();

    // Optionally, check for game win conditions if all mines are flagged
    // if(m_board.checkWinCondition()) { /* Handle win */ }
}

void MainWindow::updateBoardDisplay()
{
    // Loop over every cell and update its corresponding QPushButton text
    for(int r = 0; r < m_board.rowCount(); r++) {
        for(int c = 0; c < m_board.colCount(); c++) {
            Cell &cell = m_board.getCell(r,c);
            QRightClickButton *btn = m_buttons[r][c];

            if(cell.isRevealed()) {
                if(cell.isMine()) {
                    // If it's a mine, display "*"
                    btn->setText("*");
                    btn->setStyleSheet("background-color: red;");
                    btn->setEnabled(false);
                } else {
                    // Show the adjacent mine count
                    int adj = cell.adjacentMines();
                    btn->setText(adj > 0 ? QString::number(adj) : "");
                    btn->setEnabled(false);
                }
            }
            else {
                if(cell.isFlagged()) {
                    // Show flag (e.g., "F") if flagged
                    btn->setText("F");
                    btn->setStyleSheet("background-color: yellow;");
                }
                else {
                    // Hidden cell: show blank or some placeholder
                    btn->setText("");
                    btn->setStyleSheet("");
                }
                // Keep it enabled so user can click it
                btn->setEnabled(true);
            }
        }
    }
}

void MainWindow::setupBoardGUI()
{
    // Optionally used if you want to separate GUI creation logic; 
    // in this example, we do everything in the constructor.
}
