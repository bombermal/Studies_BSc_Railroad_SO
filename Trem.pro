#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T11:14:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Trem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    semaforo.cpp \
    trem.cpp

HEADERS  += mainwindow.h \
    semaforo.h \
    trem.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread
