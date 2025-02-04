#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QApplication>
#include "Board.h"
#include "QRightClickButton.h"

/**
 * @brief The MainWindow class
 *
 * Represents the main window of the Minesweeper application. It sets up the UI layout,
 * integrates the custom title bar, manages the game board and its display, and handles
 * user interactions such as left and right clicks on the cells.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow Constructs a new MainWindow.
     * @param parent Pointer to the parent widget (default is nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief ~MainWindow Destructor.
     */
    ~MainWindow();

private slots:
    /**
     * @brief handleCellClick Handles left-click events on board cells.
     *
     * Reveals the clicked cell and, if applicable, triggers a board reveal on game over
     * or checks for a win condition.
     */
    void handleCellClick();

    /**
     * @brief handleCellRightClick Handles right-click events on board cells.
     *
     * Toggles the flag state of the cell and checks for a win condition.
     */
    void handleCellRightClick();

    /**
     * @brief onWinRetry Slot for handling a retry after a win.
     */
    void onWinRetry();

    /**
     * @brief onWinExit Slot for handling application exit after a win.
     */
    void onWinExit();

    /**
     * @brief onLoseRetry Slot for handling a retry after a loss.
     */
    void onLoseRetry();

    /**
     * @brief onLoseExit Slot for handling application exit after a loss.
     */
    void onLoseExit();

private:
    /**
     * @brief updateBoardDisplay Refreshes the UI to reflect the current state of the board.
     */
    void updateBoardDisplay();

    /**
     * @brief showWinMessage Displays a message box when the player wins.
     */
    void showWinMessage();

    /**
     * @brief showLoseMessage Displays a message box when the player loses.
     */
    void showLoseMessage();

    /**
     * @brief resetBoard Resets the board to start a new game.
     */
    void resetBoard();

    Board m_board;   ///< The Minesweeper game board.
    QVector<QVector<QRightClickButton*>> m_buttons;  ///< Grid of buttons representing each cell.

    int m_losingRow; ///< Row index of the cell that triggered a loss.
    int m_losingCol; ///< Column index of the cell that triggered a loss.
};

#endif
