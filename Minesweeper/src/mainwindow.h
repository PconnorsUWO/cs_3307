#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QApplication>
#include "Board.h"
#include "QRightClickButton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleCellClick();
    void handleCellRightClick();
    void onWinRetry();
    void onWinExit();
    void onLoseRetry();
    void onLoseExit();

private:
    void updateBoardDisplay();
    void showWinMessage();
    void showLoseMessage();
    void resetBoard();

    Board m_board;
    QVector<QVector<QRightClickButton*>> m_buttons;

    // Coordinates of the cell that caused the loss.
    int m_losingRow;
    int m_losingCol;
};

#endif