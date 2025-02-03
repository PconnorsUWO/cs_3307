#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

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
    for(int r = 0; r < m_board.rowCount(); r++) {
        for(int c = 0; c < m_board.colCount(); c++) {
            Cell &cell = m_board.getCell(r,c);
            QRightClickButton *btn = m_buttons[r][c];

            if(cell.isRevealed()) {
                if(cell.isMine()) {
                    btn->setText("*");
                    btn->setStyleSheet("background-color: red;");
                    btn->setEnabled(false);
                } else {
                    int adj = cell.adjacentMines();
                    btn->setText(adj > 0 ? QString::number(adj) : "");
                    btn->setEnabled(false);
                }
            }
            else {
                if(cell.isFlagged()) {
                    btn->setText("F");
                    btn->setStyleSheet("background-color: yellow;");
                }
                else {
                    btn->setText("");
                    btn->setStyleSheet("");
                }
                btn->setEnabled(true);
            }
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
