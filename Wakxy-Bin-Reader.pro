#-------------------------------------------------
#
# Project created by QtCreator 2015-01-02T20:20:41
#
#-------------------------------------------------

QT       += core gui concurrent script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wakxy-Bin-Reader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    binarydocument.cpp \
    binarydocumentindex.cpp \
    randombytebufferreader.cpp \
    binarydocumentscript.cpp

HEADERS  += mainwindow.h \
    binarydocument.h \
    binarydocumentindex.h \
    randombytebufferreader.h \
    binarydocumentscript.h

FORMS    += mainwindow.ui
