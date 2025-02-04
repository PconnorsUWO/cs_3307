#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Check for resource existence before creating the main window.
    if (!QFile::exists(":/resources/flag.png")) {
        qCritical() << "Critical resource missing: :/resources/flag.png";
        QMessageBox::critical(nullptr, "Critical Error", "Required resource missing: flag icon not found. The application will now exit.");
        return EXIT_FAILURE;  // Exit the program if resource not found.
    }

    MainWindow w;
    w.show();
    return app.exec();
}