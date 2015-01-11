#-------------------------------------------------
#
# Project created by QtCreator 2015-01-02T20:20:41
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wakxy-Bin-Reader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    binarydocument.cpp \
    binarydocumentindex.cpp \
    randombytebufferreader.cpp

HEADERS  += mainwindow.h \
    binarydocument.h \
    binarydocumentindex.h \
    randombytebufferreader.h

FORMS    += mainwindow.ui
