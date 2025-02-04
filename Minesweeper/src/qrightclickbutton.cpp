#include "qrightclickbutton.h"

/**
 * @brief QRightClickButton::QRightClickButton Constructs a QRightClickButton.
 * @param parent Pointer to the parent widget.
 *
 * Simply calls the base class constructor.
 */
QRightClickButton::QRightClickButton(QWidget *parent) :
    QPushButton(parent)
{
}

/**
 * @brief QRightClickButton::mousePressEvent Handles mouse press events.
 * @param e The mouse event.
 *
 * If the event corresponds to a right-click, the custom signal rightClicked is emitted.
 * Afterwards, the default QPushButton behavior for mouse press events is executed.
 */
void QRightClickButton::mousePressEvent(QMouseEvent *e)
{
    // Check if the right mouse button was pressed.
    if (e->button() == Qt::RightButton) {
        emit rightClicked();
    }
    // Call the base class implementation to handle other behaviors.
    QPushButton::mousePressEvent(e);
}
