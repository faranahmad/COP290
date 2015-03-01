#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T11:46:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp \
    onlineusers.cpp \
    allusers.cpp \
    serverfilesandfolders.cpp

HEADERS  += server.h \
    onlineusers.h \
    allusers.h \
    serverfilesandfolders.h

FORMS    += server.ui \
    onlineusers.ui \
    allusers.ui \
    serverfilesandfolders.ui
CONFIG += c++11
