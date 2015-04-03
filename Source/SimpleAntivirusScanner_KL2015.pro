#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T19:21:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleAntivirusScanner_KL2015
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        fileinfo.cpp \
    generalexception.cpp

HEADERS  += mainwindow.h \
        fileinfo.h \
    generalexception.h

FORMS    += mainwindow.ui
