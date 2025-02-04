#ifndef QRIGHTCLICKBUTTON_H
#define QRIGHTCLICKBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

/**
 * @brief The QRightClickButton class
 *
 * A subclass of QPushButton that emits a custom signal when the right mouse button is clicked.
 * This allows for distinct handling of right-click events in the Minesweeper game.
 */
class QRightClickButton : public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief QRightClickButton Constructor.
     * @param parent Pointer to the parent widget (default is nullptr).
     */
    explicit QRightClickButton(QWidget *parent = nullptr);

signals:
    /**
     * @brief rightClicked Signal emitted when the button is right-clicked.
     */
    void rightClicked();

protected:
    /**
     * @brief mousePressEvent Overrides the mouse press event.
     * @param e The mouse event.
     *
     * If the right mouse button is pressed, the rightClicked signal is emitted.
     * Then the base class's mousePressEvent is called.
     */
    void mousePressEvent(QMouseEvent *e) override;
};

#endif // QRIGHTCLICKBUTTON_H
