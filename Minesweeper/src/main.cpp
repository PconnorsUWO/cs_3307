#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"

/**
 * @brief main The entry point of the Minesweeper application.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE if a critical resource is missing.
 *
 * The main function creates a QApplication, checks for the existence of a critical resource
 * (flag icon), and then instantiates and displays the main window. If the resource is missing,
 * an error is shown and the application exits.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Check if the required resource (flag icon) exists.
    if (!QFile::exists(":/resources/flag.png")) {
        qCritical() << "Critical resource missing: :/resources/flag.png";
        QMessageBox::critical(nullptr, "Critical Error", "Required resource missing: flag icon not found. The application will now exit.");
        return EXIT_FAILURE;  // Exit if the required resource is missing.
    }

    // Create and show the main window.
    MainWindow w;
    w.show();
    return app.exec();
}
