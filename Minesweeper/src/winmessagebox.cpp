#include "WinMessageBox.h"
#include <QIcon>

WinMessageBox::WinMessageBox(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Congratulations!");
    setModal(true);
    setFixedSize(300, 150);

    // Icon Label
    QLabel *iconLabel = new QLabel(this);
    QIcon icon(":/icons/win_icon.png"); // Ensure you have a win_icon.png in your resources
    iconLabel->setPixmap(icon.pixmap(64, 64));
    iconLabel->setAlignment(Qt::AlignCenter);

    // Message Label
    QLabel *messageLabel = new QLabel("You won!", this);
    messageLabel->setAlignment(Qt::AlignCenter);
    QFont font = messageLabel->font();
    font.setPointSize(14);
    font.setBold(true);
    messageLabel->setFont(font);

    // Buttons
    retryButton = new QPushButton("Retry", this);
    exitButton = new QPushButton("Exit", this);

    // Connect buttons to signals
    connect(retryButton, &QPushButton::clicked, this, &WinMessageBox::retryClicked);
    connect(exitButton, &QPushButton::clicked, this, &WinMessageBox::exitClicked);

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
