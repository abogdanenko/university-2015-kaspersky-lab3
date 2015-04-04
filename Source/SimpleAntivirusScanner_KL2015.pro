#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T19:21:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleAntivirusScanner_KL2015
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        scannermainwindow.cpp \
        fileinfo.cpp \
    generalexception.cpp \
    filebrowser.cpp

HEADERS  += scannermainwindow.h \
        fileinfo.h \
    generalexception.h \
    filebrowser.h
