#-------------------------------------------------
#
# Project created by QtCreator 2020-01-21T09:58:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HD_KeyRing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    HD_KeyRing.cpp

HEADERS  += mainwindow.h \
    HD_KeyRing.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lbitcoin

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../../usr/lib/i386-linux-gnu/ -lboost_system

INCLUDEPATH += $$PWD/../../../../../usr/lib/i386-linux-gnu
DEPENDPATH += $$PWD/../../../../../usr/lib/i386-linux-gnu
