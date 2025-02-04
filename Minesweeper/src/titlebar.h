#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPoint>

/**
 * @brief The TitleBar class
 *
 * Implements a custom title bar widget for the Minesweeper game.
 * This widget replaces the native window decorations and provides custom
 * minimize and close buttons, as well as window dragging functionality.
 */
class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief TitleBar Constructs a TitleBar widget.
     * @param parent Pointer to the parent widget (default is nullptr).
     */
    explicit TitleBar(QWidget *parent = nullptr);

signals:
    /**
     * @brief minimizeRequested Signal emitted when the minimize button is clicked.
     */
    void minimizeRequested();

    /**
     * @brief closeRequested Signal emitted when the close button is clicked.
     */
    void closeRequested();

protected:
    /**
     * @brief mousePressEvent Handles mouse press events to enable window dragging.
     * @param event Pointer to the QMouseEvent.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief mouseMoveEvent Handles mouse move events to enable window dragging.
     * @param event Pointer to the QMouseEvent.
     */
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QLabel *m_iconLabel;      ///< Displays an icon in the title bar.
    QLabel *m_titleLabel;     ///< Displays the title text.
    QPushButton *m_minimizeButton;  ///< Button to minimize the window.
    QPushButton *m_closeButton;     ///< Button to close the window.
    QPoint m_dragPosition;    ///< Stores the offset used during window dragging.
};

#endif // TITLEBAR_H
