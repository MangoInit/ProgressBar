#-------------------------------------------------
#
# Project created by QtCreator 2018-11-30T10:02:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProgressBar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workerthread.cpp \
    findfile.cpp

HEADERS  += mainwindow.h \
    workerthread.h \
    findfile.h

FORMS    += mainwindow.ui

QT +=concurrent
