#-------------------------------------------------
#
# Project created by QtCreator 2014-02-02T07:40:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Odessa
TEMPLATE = app

VERSION = 0.0.70
QMAKE_TARGET_COMPANY = Swing Innovations
QMAKE_TARGET_PRODUCT = Odessa
QMAKE_TARGET_DESCRIPTION = Odessa
QMAKE_TARGET_COPYRIGHT = LGPL v2.1

SOURCES += main.cpp\
        mainwindow.cpp \
    Graphics/Bitmap/bitmapimage.cpp \
    Structure/object.cpp \
    Structure/layer.cpp \
    Structure/editor.cpp \
    Interface/dialogwindows.cpp \
    Interface/dockwidgets.cpp \
    Structure/brush.cpp

HEADERS  += mainwindow.h \
    Graphics/Bitmap/bitmapimage.h \
    Structure/object.h \
    Structure/layer.h \
    Structure/editor.h \
    Interface/dialogwindows.h \
    Interface/dockwidgets.h \
    Structure/brush.h
