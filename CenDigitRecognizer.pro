#-------------------------------------------------
#
# Project created by QtCreator 2012-11-08T09:08:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CenDigitRecognizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cdigitneuron.cpp \
    cpixelmatrix.cpp \
    cweightsreader.cpp

HEADERS  += mainwindow.h \
    cdigitneuron.h \
    cpixelmatrix.h \
    settings.h \
    cweightsreader.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    README.md
