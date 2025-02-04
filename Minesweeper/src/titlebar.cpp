#include "titlebar.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QApplication>
#include <QStyle>
#include <QGraphicsDropShadowEffect>

/**
 * @brief TitleBar::TitleBar Constructs a custom title bar for the application.
 * @param parent Pointer to the parent widget.
 *
 * This constructor sets up the layout, icons, title, and buttons (minimize and close)
 * and applies a custom style and drop shadow effect.
 */
TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    // Set an object name so the style sheet can target this widget.
    setObjectName("TitleBar");
    // Fix the height of the title bar.
    setFixedHeight(35);

    // Create a horizontal layout with margins.
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 0, 10, 0);

    // Create and add an icon label.
    m_iconLabel = new QLabel(this);
    QPixmap icon(":/resources/bomb-revealed.png");  // Replace with your own Minesweeper icon.
    m_iconLabel->setPixmap(icon.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    layout->addWidget(m_iconLabel);

    // Create and add the title label.
    m_titleLabel = new QLabel("Minesweeper", this);
    m_titleLabel->setStyleSheet("color: white; font-family: 'Segoe UI'; font-size: 16px; font-weight: bold;");
    layout->addWidget(m_titleLabel);

    // Add a stretch to push the buttons to the right.
    layout->addStretch();

    // Create the minimize button.
    m_minimizeButton = new QPushButton(this);
    m_minimizeButton->setFixedSize(30, 30);
    m_minimizeButton->setText("—");  // Em dash for a clean look.
    m_minimizeButton->setStyleSheet(
        "QPushButton {"
        "  background-color: transparent;"
        "  border: none;"
        "  color: black;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "  background-color: rgba(255, 255, 255, 0.3);"
        "  border-radius: 5px;"
        "}"
    );
    layout->addWidget(m_minimizeButton);

    // Create the close button.
    m_closeButton = new QPushButton(this);
    m_closeButton->setFixedSize(30, 30);
    m_closeButton->setText("✕");  // Unicode multiplication sign.
    m_closeButton->setStyleSheet(
        "QPushButton {"
        "  background-color: transparent;"
        "  border: none;"
        "  color: black;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #E81123;"  // Bold red for hover.
        "  border-radius: 5px;"
        "}"
    );
    layout->addWidget(m_closeButton);

    // Apply a gradient background to the title bar.
    setStyleSheet(
        "#TitleBar {"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #34495e, stop:1 #2c3e50);"
        "}"
    );

    // Add a drop shadow effect for depth.
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setOffset(0, 2);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);

    // Connect the buttons to the corresponding signals.
    connect(m_minimizeButton, &QPushButton::clicked, this, &TitleBar::minimizeRequested);
    connect(m_closeButton, &QPushButton::clicked, this, &TitleBar::closeRequested);
}

/**
 * @brief TitleBar::mousePressEvent Handles mouse press events for window dragging.
 * @param event Pointer to the QMouseEvent.
 *
 * This function allows the user to drag the window by clicking and holding the title bar.
 */
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Use globalPosition() and convert it to QPoint.
        m_dragPosition = event->globalPosition().toPoint() - parentWidget()->frameGeometry().topLeft();
        event->accept();
    }
}

/**
 * @brief TitleBar::mouseMoveEvent Handles mouse move events for window dragging.
 * @param event Pointer to the QMouseEvent.
 *
 * This function moves the window according to the mouse drag movement.
 */
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        parentWidget()->move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}


