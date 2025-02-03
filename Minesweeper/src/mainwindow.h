#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QApplication>
#include "Board.h"
#include "QRightClickButton.h"
#include "WinMessageBox.h"
#include "LoseMessageBox.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
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
    void resetBoard();

    Board m_board;
    QVector<QVector<QRightClickButton*>> m_buttons;
};

#endif