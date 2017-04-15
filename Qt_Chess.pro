# Шахматы - основной файл проекта

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    chessboard.cpp \
    chesspiece.cpp

HEADERS  += mainwindow.h \
    game.h \
    chessboard.h \
    chesspiece.h \
    addition.h

FORMS    += mainwindow.ui \
    chessboard.ui

RESOURCES += \
    data.qrc
