#-------------------------------------------------
# Project configuration
#-------------------------------------------------

QT       += core gui widgets
CONFIG   += c++11     # or c++17, depending on your needs

TARGET = Minesweeper
TEMPLATE = app

#-------------------------------------------------
# Include paths
#-------------------------------------------------

INCLUDEPATH += src

#-------------------------------------------------
# Source files and header files
#-------------------------------------------------

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/board.cpp \
    src/cell.cpp

HEADERS += \
    src/mainwindow.h \
    src/board.h \
    src/cell.h

#-------------------------------------------------
# Resource files (optional, if you create .qrc files)
#-------------------------------------------------

# RESOURCES += resources.qrc
