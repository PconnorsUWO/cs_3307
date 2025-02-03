#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QIcon>   
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_board.initialize();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout *layout = new QGridLayout(centralWidget);
    centralWidget->setLayout(layout);

    m_buttons.resize(m_board.rowCount());
    for(int r = 0; r < m_board.rowCount(); r++) {
        m_buttons[r].resize(m_board.colCount());
        for(int c = 0; c < m_board.colCount(); c++) {
            QRightClickButton *btn = new QRightClickButton(this);
            btn->setFixedSize(40, 40);
            layout->addWidget(btn, r, c);
            m_buttons[r][c] = btn;

            connect(btn, &QPushButton::clicked, this, &MainWindow::handleCellClick);

            connect(btn, &QRightClickButton::rightClicked, this, &MainWindow::handleCellRightClick);
        }
    }

    updateBoardDisplay();
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleCellClick()
{
    QRightClickButton *clickedButton = qobject_cast<QRightClickButton*>(sender());
    if(!clickedButton) return;

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

    m_board.revealCell(clickedRow, clickedCol);

    updateBoardDisplay();

    if(m_board.getCell(clickedRow, clickedCol).isMine()) {

        return; 
    }

    if(m_board.checkWinCondition()) {

        return; 
    }
}

void MainWindow::handleCellRightClick()
{
    QRightClickButton *clickedButton = qobject_cast<QRightClickButton*>(sender());
    if(!clickedButton) return;

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

    m_board.toggleFlag(clickedRow, clickedCol);

    updateBoardDisplay();

    if(m_board.checkWinCondition()) {

        return; 
    }
}

void MainWindow::updateBoardDisplay()
{
    // Loop over every cell and update its corresponding QRightClickButton icon
    for (int r = 0; r < m_board.rowCount(); r++) {
        for (int c = 0; c < m_board.colCount(); c++) {
            Cell &cell = m_board.getCell(r, c);
            QRightClickButton *btn = m_buttons[r][c];

            // Clear any previous text or icon
            btn->setText("");
            btn->setIcon(QIcon());

            if (cell.isRevealed()) {
                if (cell.isMine()) {
                    // Display bomb image for a revealed mine.
                    // (You might use bomb-explode.png if you want to indicate the mine that was clicked.)
                    btn->setIcon(QIcon(":/icons/bomb-revealed.png"));
                } else {
                    int adj = cell.adjacentMines();
                    if (adj > 0) {
                        // Display the numbered tile icon corresponding to the count (1-tile.png, 2-tile.png, etc.)
                        btn->setIcon(QIcon(QString(":/icons/%1-tile.png").arg(adj)));
                    } else {
                        // For 0 adjacent mines, display the clicked tile image.
                        btn->setIcon(QIcon(":/icons/general-tile-clicked.png"));
                    }
                }
                btn->setEnabled(false);
            }
            else {
                if (cell.isFlagged()) {
                    // Display the flag image when the cell is flagged.
                    btn->setIcon(QIcon(":/icons/flag.png"));
                } else {
                    // Display the covered tile image for unrevealed cells.
                    btn->setIcon(QIcon(":/icons/general-tile.png"));
                }
                btn->setEnabled(true);
            }
            // Adjust the icon size to match the button size.
            btn->setIconSize(btn->size());
        }
    }
}

void MainWindow::resetBoard()
{
    m_board.initialize();
    updateBoardDisplay();
}

void MainWindow::onWinRetry()
{
    resetBoard();
}

void MainWindow::onWinExit()
{
    QApplication::quit();
}

void MainWindow::onLoseRetry()
{
    resetBoard();
}

void MainWindow::onLoseExit()
{
    QApplication::quit();
}
