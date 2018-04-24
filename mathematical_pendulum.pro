#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T13:53:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mathematical_pendulum
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wirependulum.cpp

HEADERS  += mainwindow.h \
    wirependulum.h

FORMS    += mainwindow.ui

RESOURCES     = images.qrc
