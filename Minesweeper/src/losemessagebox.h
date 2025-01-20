#ifndef LOSEMESSAGEBOX_H
#define LOSEMESSAGEBOX_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class LoseMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit LoseMessageBox(QWidget *parent = nullptr);

signals:
    void retryClicked();
    void exitClicked();

private:
    QPushButton *retryButton;
    QPushButton *exitButton;
};

#endif // LOSEMESSAGEBOX_H
