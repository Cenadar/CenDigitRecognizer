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
    cdigitrecognizer.cpp \
    cworkinterface.cpp \
    cpixelmatrixbuilder.cpp \
    cviewinterface.cpp \
    libs/nightcharts.cpp \
    drawpad.cpp \
    histogramview.cpp \
    cdigitneuronreader.cpp \
    cdigitneuronbuilder.cpp \
    cxmlwriter.cpp \
    cmessageshower.cpp \
    cpixelmatrixreader.cpp \
    cxmlparser.cpp \
    settings.cpp \
    neurondisplay.cpp \
    cneuronpainter.cpp \
    domutils.cpp \
    iconverter.cpp

HEADERS  += mainwindow.h \
    cdigitneuron.h \
    cpixelmatrix.h \
    settings.h \
    cdigitrecognizer.h \
    cworkinterface.h \
    cpixelmatrixbuilder.h \
    cviewinterface.h \
    libs/nightcharts.h \
    drawpad.h \
    histogramview.h \
    cdigitneuronreader.h \
    cdigitneuronbuilder.h \
    cxmlwriter.h \
    cmessageshower.h \
    cpixelmatrixreader.h \
    cxmlparser.h \
    neurondisplay.h \
    cneuronpainter.h \
    domutils.h \
    iconverter.h

FORMS    += mainwindow.ui \
    neurondisplay.ui

OTHER_FILES += \
    README.md
