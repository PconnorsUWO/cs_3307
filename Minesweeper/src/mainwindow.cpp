#include "mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <QIcon>
#include <QPixmap>
#include <QSize>

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
    for (int r = 0; r < m_board.rowCount(); r++) {
        for (int c = 0; c < m_board.colCount(); c++) {
            Cell &cell = m_board.getCell(r, c);
            QRightClickButton *btn = m_buttons[r][c];

            // Reset the button text and icon
            btn->setText("");
            btn->setIcon(QIcon());

            QString iconPath;

            if (cell.isRevealed()) {
                if (cell.isMine()) {
                    iconPath = ":/resources/bomb-revealed.png";
                } else {
                    int adj = cell.adjacentMines();
                    if (adj > 0) {
                        iconPath = QString(":/resources/%1-tile.png").arg(adj);
                    } else {
                        iconPath = ":/resources/general-tile-clicked.png";
                    }
                }
                btn->setEnabled(false);
            }
            else {
                if (cell.isFlagged()) {
                    iconPath = ":/resources/flag.png";
                } else {
                    iconPath = ":/resources/general-tile.png";
                }
                btn->setEnabled(true);
            }

            // Load the pixmap from the resource path
            QPixmap pixmap(iconPath);
            if (!pixmap.isNull()) {
                // Explicitly scale the pixmap to the button size, preserving aspect ratio
                QPixmap scaledPixmap = pixmap.scaled(btn->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                btn->setIcon(QIcon(scaledPixmap));
                btn->setIconSize(btn->size());
            } else {
                qWarning() << "[Error] Failed to load icon:" << iconPath;
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
