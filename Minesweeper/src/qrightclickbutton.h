#ifndef QRIGHTCLICKBUTTON_H
#define QRIGHTCLICKBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class QRightClickButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QRightClickButton(QWidget *parent = nullptr);

signals:
    void rightClicked();

protected:
    void mousePressEvent(QMouseEvent *e) override;
};

#endif // QRIGHTCLICKBUTTON_H
