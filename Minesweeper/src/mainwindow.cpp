#include "mainwindow.h"
#include "titlebar.h"       
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_losingRow(-1)      // initialize to an invalid value
    , m_losingCol(-1)
{
    // Remove native window decorations.
    setWindowFlags(Qt::FramelessWindowHint);

    // Create a central widget for the main window.
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a vertical layout that will hold the custom title bar and the game board.
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Create and add the custom title bar.
    TitleBar *titleBar = new TitleBar(this);
    mainLayout->addWidget(titleBar);

    // Connect the title bar signals to window actions.
    connect(titleBar, &TitleBar::minimizeRequested, this, &MainWindow::showMinimized);
    connect(titleBar, &TitleBar::closeRequested, this, &MainWindow::close);

    // Create a widget to hold the game board.
    QWidget *boardWidget = new QWidget(this);
    
    // Use a grid layout for the Minesweeper board.
    QGridLayout *gridLayout = new QGridLayout(boardWidget);
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(0);
    gridLayout->setContentsMargins(-30, 0, -30, 0);
    boardWidget->setLayout(gridLayout);

    // Add the board widget to the main layout.
    mainLayout->addWidget(boardWidget);

    // Initialize your board and buttons as before.
    m_board.initialize();

    // Resize the m_buttons container.
    m_buttons.resize(m_board.rowCount());
    for (int r = 0; r < m_board.rowCount(); r++) {
        m_buttons[r].resize(m_board.colCount());
        for (int c = 0; c < m_board.colCount(); c++) {
            QRightClickButton *btn = new QRightClickButton(this);
            btn->setFixedSize(40, 40);
            
            // Remove any default borders/paddings that might create spacing.
            btn->setStyleSheet("border: none; padding: -1px; margin: 0px;");
            
            gridLayout->addWidget(btn, r, c);
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
    if (!clickedButton)
        return;

    int clickedRow = -1;
    int clickedCol = -1;
    for (int r = 0; r < m_board.rowCount(); r++) {
        for (int c = 0; c < m_board.colCount(); c++) {
            if (m_buttons[r][c] == clickedButton) {
                clickedRow = r;
                clickedCol = c;
                break;
            }
        }
        if (clickedRow != -1)
            break;
    }

    if (clickedRow == -1 || clickedCol == -1) {
        qWarning() << "Clicked button not found in the grid.";
        return;
    }

    m_board.revealCell(clickedRow, clickedCol);
    updateBoardDisplay();

    // Check if the clicked cell is a mine (loss)
    if (m_board.getCell(clickedRow, clickedCol).isMine()) {
        // Store the coordinates of the losing cell so that updateBoardDisplay()
        // can display bomb-explode.png for that cell.
        m_losingRow = clickedRow;
        m_losingCol = clickedCol;

        // Reveal the entire board and update the display.
        m_board.revealBoard();
        updateBoardDisplay();

        // Now show the lose message.
        showLoseMessage();
        return;
    }

    // Check win condition.
    if (m_board.checkWinCondition()) {
        m_board.revealBoard();
        updateBoardDisplay();
        showWinMessage();
        return;
    }
}

void MainWindow::handleCellRightClick()
{
    QRightClickButton *clickedButton = qobject_cast<QRightClickButton*>(sender());
    if (!clickedButton)
        return;

    int clickedRow = -1;
    int clickedCol = -1;
    for (int r = 0; r < m_board.rowCount(); r++) {
        for (int c = 0; c < m_board.colCount(); c++) {
            if (m_buttons[r][c] == clickedButton) {
                clickedRow = r;
                clickedCol = c;
                break;
            }
        }
        if (clickedRow != -1)
            break;
    }

    if (clickedRow == -1 || clickedCol == -1) {
        qWarning() << "Right-clicked button not found in the grid.";
        return;
    }

    m_board.toggleFlag(clickedRow, clickedCol);
    updateBoardDisplay();

    if (m_board.checkWinCondition()) {
        showWinMessage();
        return;
    }
}

void MainWindow::updateBoardDisplay()
{
    for (int r = 0; r < m_board.rowCount(); r++) {
        for (int c = 0; c < m_board.colCount(); c++) {
            Cell &cell = m_board.getCell(r, c);
            QRightClickButton *btn = m_buttons[r][c];

            // Clear previous text and icon.
            btn->setText("");
            btn->setIcon(QIcon());

            QString iconPath;
            if (cell.isRevealed()) {
                if (cell.isMine()) {
                    // If this is the losing cell, use bomb-explode icon.
                    if (r == m_losingRow && c == m_losingCol)
                        iconPath = ":/resources/bomb-explode.png";
                    else
                        iconPath = ":/resources/bomb-revealed.png";
                } else {
                    int adj = cell.adjacentMines();
                    if (adj > 0)
                        iconPath = QString(":/resources/%1-tile.png").arg(adj);
                    else
                        iconPath = ":/resources/general-tile-clicked.png";
                }
                btn->setEnabled(false);
            } else {
                if (cell.isFlagged())
                    iconPath = ":/resources/flag.png";
                else
                    iconPath = ":/resources/general-tile.png";
                btn->setEnabled(true);
            }

            QPixmap pixmap(iconPath);
            if (!pixmap.isNull()) {
                QPixmap scaledPixmap = pixmap.scaled(btn->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                QIcon icon;
                icon.addPixmap(scaledPixmap, QIcon::Normal);
                icon.addPixmap(scaledPixmap, QIcon::Disabled);
                btn->setIcon(icon);
                btn->setIconSize(btn->size());
            } else {
                qWarning() << "[Error] Failed to load icon:" << iconPath;
            }
        }
    }
}

void MainWindow::showWinMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("You Win!");
    msgBox.setText("Congratulations! You've cleared the board.");
    msgBox.setIcon(QMessageBox::Information);

    // Add Retry and Exit buttons.
    QPushButton *retryButton = msgBox.addButton("Retry", QMessageBox::AcceptRole);
    QPushButton *exitButton = msgBox.addButton("Exit", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == retryButton) {
        resetBoard();
    } else {
        QApplication::quit();
    }
}

void MainWindow::showLoseMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("You Lose!");
    msgBox.setText("Oops! You clicked on a bomb.");
    msgBox.setIcon(QMessageBox::Critical);

    // Add Retry and Exit buttons.
    QPushButton *retryButton = msgBox.addButton("Retry", QMessageBox::AcceptRole);
    QPushButton *exitButton = msgBox.addButton("Exit", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == retryButton) {
        resetBoard();
    } else {
        QApplication::quit();
    }
}

void MainWindow::resetBoard()
{
    m_board.initialize();
    // Reset the losing cell coordinates.
    m_losingRow = -1;
    m_losingCol = -1;
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
