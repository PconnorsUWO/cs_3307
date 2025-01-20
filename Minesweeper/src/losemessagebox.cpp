#include "LoseMessageBox.h"
#include <QIcon>

LoseMessageBox::LoseMessageBox(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Game Over");
    setModal(true);
    setFixedSize(300, 150);

    // Icon Label
    QLabel *iconLabel = new QLabel(this);
    QIcon icon(":/icons/lose_icon.png"); // Ensure you have a lose_icon.png in your resources
    iconLabel->setPixmap(icon.pixmap(64, 64));
    iconLabel->setAlignment(Qt::AlignCenter);

    // Message Label
    QLabel *messageLabel = new QLabel("You clicked on a mine!", this);
    messageLabel->setAlignment(Qt::AlignCenter);
    QFont font = messageLabel->font();
    font.setPointSize(14);
    font.setBold(true);
    messageLabel->setFont(font);

    // Buttons
    retryButton = new QPushButton("Retry", this);
    exitButton = new QPushButton("Exit", this);

    // Connect buttons to signals
    connect(retryButton, &QPushButton::clicked, this, &LoseMessageBox::retryClicked);
    connect(exitButton, &QPushButton::clicked, this, &LoseMessageBox::exitClicked);

    // Layouts
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(retryButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(iconLabel);
    mainLayout->addWidget(messageLabel);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}
