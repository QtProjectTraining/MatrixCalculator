#-------------------------------------------------
#
# Project created by QtCreator 2018-07-12T14:44:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MatrixCalculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    csv.cpp \
    doubleform.cpp \
    mymatrix.cpp

HEADERS  += mainwindow.h \
    csv.h \
    doubleform.h \
    mymatrix.h

FORMS    += mainwindow.ui \
    doubleform.ui

INCLUDEPATH+=C:\eigen-eigen-5a0156e40feb\eigen-eigen-5a0156e40feb\Eigen

RESOURCES += \
    images.qrc
