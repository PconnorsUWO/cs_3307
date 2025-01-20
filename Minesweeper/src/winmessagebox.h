#ifndef WINMESSAGEBOX_H
#define WINMESSAGEBOX_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class WinMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit WinMessageBox(QWidget *parent = nullptr);

signals:
    void retryClicked();
    void exitClicked();

private:
    QPushButton *retryButton;
    QPushButton *exitButton;
};

#endif // WINMESSAGEBOX_H
