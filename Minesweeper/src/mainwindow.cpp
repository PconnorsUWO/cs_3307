#include "mainwindow.h"
#include "titlebar.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QPixmap>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QApplication>

/**
 * @brief MainWindow::MainWindow Constructs the main window of the Minesweeper game.
 * @param parent Pointer to the parent widget.
 *
 * This constructor sets up the custom title bar, creates the grid layout for the game board,
 * initializes the board and buttons, and connects the necessary signals for cell interactions.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_losingRow(-1)      // Initialize to an invalid value.
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

    // Initialize the game board.
    m_board.initialize();

    // Resize and populate the m_buttons container with custom right-click buttons.
    m_buttons.resize(m_board.rowCount());
    for (int r = 0; r < m_board.rowCount(); r++) {
        m_buttons[r].resize(m_board.colCount());
        for (int c = 0; c < m_board.colCount(); c++) {
            QRightClickButton *btn = new QRightClickButton(this);
            btn->setFixedSize(40, 40);
            
            // Remove default borders/paddings.
            btn->setStyleSheet("border: none; padding: -1px; margin: 0px;");
            
            gridLayout->addWidget(btn, r, c);
            m_buttons[r][c] = btn;

            connect(btn, &QPushButton::clicked, this, &MainWindow::handleCellClick);
            connect(btn, &QRightClickButton::rightClicked, this, &MainWindow::handleCellRightClick);
        }
    }

    // Refresh the board display to match the initial game state.
    updateBoardDisplay();
}

/**
 * @brief MainWindow::~MainWindow Destructor.
 */
MainWindow::~MainWindow()
{
}

/**
 * @brief MainWindow::handleCellClick Slot that processes left-click events on cells.
 *
 * Determines which button was clicked, reveals the corresponding cell,
 * checks for a mine (loss), and verifies if the win condition has been met.
 */
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

    // Check if the clicked cell is a mine (loss condition).
    if (m_board.getCell(clickedRow, clickedCol).isMine()) {
        // Store the coordinates of the losing cell.
        m_losingRow = clickedRow;
        m_losingCol = clickedCol;

        // Reveal the entire board.
        m_board.revealBoard();
        updateBoardDisplay();

        // Display the losing message.
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

/**
 * @brief MainWindow::handleCellRightClick Slot that processes right-click events on cells.
 *
 * This function toggles the flag status of the clicked cell and checks if the win condition is met.
 */
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

/**
 * @brief MainWindow::updateBoardDisplay Updates the UI representation of the board.
 *
 * Iterates over each cell, updating the text, icon, and enabled state of each button
 * based on the corresponding cell's status (revealed, mine, flagged, or number of adjacent mines).
 */
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
                    // Use bomb-explode icon for the losing cell.
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

/**
 * @brief MainWindow::showWinMessage Displays a message box indicating the player has won.
 */
void MainWindow::showWinMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("You Win!");
    msgBox.setText("Congratulations! You've cleared the board.");
    msgBox.setIcon(QMessageBox::Information);

    // Add Retry and Exit buttons. (No need to store the exit button if unused)
    QPushButton *retryButton = msgBox.addButton("Retry", QMessageBox::AcceptRole);
    msgBox.addButton("Exit", QMessageBox::RejectRole);  // No variable stored

    msgBox.exec();

    if (msgBox.clickedButton() == retryButton) {
        resetBoard();
    } else {
        QApplication::quit();
    }
}

/**
 * @brief MainWindow::showLoseMessage Displays a message box indicating the player has lost.
 */
void MainWindow::showLoseMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("You Lose!");
    msgBox.setText("Oops! You clicked on a bomb.");
    msgBox.setIcon(QMessageBox::Critical);

    // Add Retry and Exit buttons.
    QPushButton *retryButton = msgBox.addButton("Retry", QMessageBox::AcceptRole);
    msgBox.addButton("Exit", QMessageBox::RejectRole);  // No variable stored

    msgBox.exec();

    if (msgBox.clickedButton() == retryButton) {
        resetBoard();
    } else {
        QApplication::quit();
    }
}

/**
 * @brief MainWindow::resetBoard Resets the game board to start a new game.
 */
void MainWindow::resetBoard()
{
    m_board.initialize();
    // Reset the losing cell coordinates.
    m_losingRow = -1;
    m_losingCol = -1;
    updateBoardDisplay();
}

/**
 * @brief MainWindow::onWinRetry Slot for retrying after a win.
 */
void MainWindow::onWinRetry()
{
    resetBoard();
}

/**
 * @brief MainWindow::onWinExit Slot for exiting the application after a win.
 */
void MainWindow::onWinExit()
{
    QApplication::quit();
}

/**
 * @brief MainWindow::onLoseRetry Slot for retrying after a loss.
 */
void MainWindow::onLoseRetry()
{
    resetBoard();
}

/**
 * @brief MainWindow::onLoseExit Slot for exiting the application after a loss.
 */
void MainWindow::onLoseExit()
{
    QApplication::quit();
}
