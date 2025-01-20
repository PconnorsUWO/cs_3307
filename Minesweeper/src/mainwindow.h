#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qrightclickbutton.h"
#include <vector>
#include "board.h"
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleCellClick();        // Slot for left-clicks
    void handleCellRightClick();   // Slot for right-clicks
    void resetBoard();


private:
    void updateBoardDisplay();
     
    

    Board m_board; // Your game board
    std::vector<std::vector<QRightClickButton*>> m_buttons;
};

#endif // MAINWINDOW_H
