#-------------------------------------------------
#
# Project created by QtCreator 2014-02-02T07:40:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Odessa
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Graphics/Bitmap/bitmapimage.cpp \
    Structure/object.cpp \
    Structure/layer.cpp \
    Structure/editor.cpp

HEADERS  += mainwindow.h \
    Graphics/Bitmap/bitmapimage.h \
    Structure/object.h \
    Structure/layer.h \
    Structure/editor.h
