#include "titlebar.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QApplication>
#include <QStyle>
#include <QGraphicsDropShadowEffect>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    // Set an object name so our style sheet can target this widget.
    setObjectName("TitleBar");
    // Set a fixed height for the title bar.
    setFixedHeight(35);

    // Create a horizontal layout with custom margins.
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 0, 10, 0);

    // Create and add an icon label.
    m_iconLabel = new QLabel(this);
    QPixmap icon(":/resources/bomb-revealed.png");  // Replace with your own Minesweeper icon.
    m_iconLabel->setPixmap(icon.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    layout->addWidget(m_iconLabel);

    // Create and add the title label with a modern font.
    m_titleLabel = new QLabel("Minesweeper", this);
    m_titleLabel->setStyleSheet("color: white; font-family: 'Segoe UI'; font-size: 16px; font-weight: bold;");
    layout->addWidget(m_titleLabel);

    // Add a stretch so the buttons are pushed to the right.
    layout->addStretch();

    // Create the minimize button.
    m_minimizeButton = new QPushButton(this);
    m_minimizeButton->setFixedSize(30, 30);
    // Set text to an em dash for a cleaner look.
    m_minimizeButton->setText("—");
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
    // Use a Unicode multiplication sign for the close button.
    m_closeButton->setText("✕");
    m_closeButton->setStyleSheet(
        "QPushButton {"
        "  background-color: transparent;"
        "  border: none;"
        "  color: black;"
        "  font-family: 'Segoe UI';"
        "  font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #E81123;"  // A bold red for the hover state.
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

    // Optionally, add a drop shadow for a subtle depth effect.
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setOffset(0, 2);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);

    // Connect button signals to your custom slots.
    connect(m_minimizeButton, &QPushButton::clicked, this, &TitleBar::minimizeRequested);
    connect(m_closeButton, &QPushButton::clicked, this, &TitleBar::closeRequested);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Store the position difference to enable smooth dragging.
        m_dragPosition = event->globalPos() - parentWidget()->frameGeometry().topLeft();
        event->accept();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        parentWidget()->move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}
