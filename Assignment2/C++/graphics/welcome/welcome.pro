#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T12:38:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = welcome
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    newusersignup.cpp \
    fileaccess.cpp

HEADERS  += login.h \
    newusersignup.h \
    fileaccess.h

FORMS    += login.ui \
    newusersignup.ui \
    fileaccess.ui
