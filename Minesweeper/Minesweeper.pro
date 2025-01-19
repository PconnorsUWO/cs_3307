QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

TEMPLATE = app
TARGET = Minesweeper

SOURCES += \
    src/main.cpp \
    src/board.cpp \
    src/cell.cpp \
    src/mainwindow.cpp \
    src/qrightclickbutton.cpp

HEADERS += \
    src/board.h \
    src/cell.h \
    src/mainwindow.h \
    src/qrightclickbutton.h
