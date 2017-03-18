#-------------------------------------------------
#
# Project created by QtCreator 2017-03-16T15:29:56
#
#-------------------------------------------------

QT       += core gui network
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CardsAgainstHumanity
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    src/cardcast/cardcastblackcard.cpp \
    src/cardcast/cardcastwhitecard.cpp \
    src/cardcast/cardcastdeck.cpp \
    src/cardcast/cardcastmodule.cpp \
    src/cardcast/cardcastservice.cpp \
    src/cardcast/cardcastcacheentry.cpp \
    src/db/pyxblackcard.cpp

HEADERS  += mainwindow.h \
    src/cardcast/cardcastblackcard.h \
    src/cardcast/cardcastwhitecard.h \
    src/cardcast/cardcastdeck.h \
    src/cardcast/cardcastmodule.h \
    src/cardcast/cardcastservice.h \
    src/cardcast/cardcastcacheentry.h \
    src/db/pyxblackcard.h

FORMS    += mainwindow.ui
