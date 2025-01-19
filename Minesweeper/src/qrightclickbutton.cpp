#include "qrightclickbutton.h"

QRightClickButton::QRightClickButton(QWidget *parent) :
    QPushButton(parent)
{
}

void QRightClickButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        emit rightClicked();
    }

    // Call the base class implementation to ensure normal button behavior
    QPushButton::mousePressEvent(e);
}
