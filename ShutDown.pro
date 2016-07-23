#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T16:45:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShutDown
TEMPLATE = app


SOURCES += main.cpp\
        shutdown.cpp \
    mytrayicon.cpp

HEADERS  += shutdown.h \
    mytrayicon.h

FORMS    += shutdown.ui

RESOURCES += \
    images.qrc

RC_FILE += \
    myicon.rc
