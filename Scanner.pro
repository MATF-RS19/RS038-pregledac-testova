#-------------------------------------------------
#
# Project created by QtCreator 2019-01-12T12:22:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scanner
TEMPLATE = app

SOURCES +=\
        mainwindow.cpp \
    waiting.cpp \
    main.cpp \
    image_processing.cpp \
    handler.cpp

HEADERS  += mainwindow.h \
    image_processing.hpp \
    handler.hpp

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib `pkg-config opencv --cflags --libs`



