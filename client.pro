#-------------------------------------------------
#
# Project created by QtCreator 2015-01-06T22:34:40
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    newserver.cpp \
    editserver.cpp \
    file.cpp \
    register.cpp

HEADERS  += mainwindow.h \
    login.h \
    newserver.h \
    editserver.h \
    file.h \
    message.h \
    headers.h \
    register.h

FORMS    += mainwindow.ui \
    login.ui \
    newserver.ui \
    editserver.ui \
    register.ui
