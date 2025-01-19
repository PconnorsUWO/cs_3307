#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qrightclickbutton.h" // Include your custom button
#include <vector>
#include "board.h" // Assuming you have a Board class managing the game state

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleCellClick();        // Slot for left-clicks
    void handleCellRightClick();   // Slot for right-clicks

private:
    void updateBoardDisplay();
    void setupBoardGUI();

    Board m_board; // Your game board
    std::vector<std::vector<QRightClickButton*>> m_buttons; // 2D array of custom buttons
};

#endif // MAINWINDOW_H
