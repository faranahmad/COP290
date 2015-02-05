#-------------------------------------------------
#
# Project created by QtCreator 2015-02-03T16:52:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = interface
TEMPLATE = app


SOURCES += main.cpp\
        interface.cpp \
    listoffiles.cpp \
    filelist.cpp \
    newuser.cpp

HEADERS  += interface.h \
    listoffiles.h \
    filelist.h \
    newuser.h

FORMS    += interface.ui \
    listoffiles.ui \
    filelist.ui \
    newuser.ui
