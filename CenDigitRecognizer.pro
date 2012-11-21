#-------------------------------------------------
#
# Project created by QtCreator 2012-11-08T09:08:02
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CenDigitRecognizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cdigitneuron.cpp \
    cpixelmatrix.cpp \
    cweightsreader.cpp \
    cweightswriter.cpp \
    cdigitrecognizer.cpp \
    cworkinterface.cpp \
    cpixelmatrixbuilder.cpp \
    cviewinterface.cpp

HEADERS  += mainwindow.h \
    cdigitneuron.h \
    cpixelmatrix.h \
    settings.h \
    cweightsreader.h \
    cweightswriter.h \
    iserializable.h \
    ivisitable.h \
    cdigitrecognizer.h \
    cworkinterface.h \
    cpixelmatrixbuilder.h \
    cviewinterface.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    README.md
