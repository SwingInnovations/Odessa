#-------------------------------------------------
#
# Project created by QtCreator 2014-02-02T07:40:41
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Odessa
TEMPLATE = app

VERSION = 0.1.0
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
    Structure/brush.cpp \
    Interface/odessa_ui.cpp \
    Structure/primitive.cpp \
    Structure/gleditor.cpp \
    Interface/panels.cpp \
    Interface/slideedit.cpp \
    Structure/Canvas/canvas.cpp \
    Interface/colorwheel.cpp

HEADERS  += mainwindow.h \
    Graphics/Bitmap/bitmapimage.h \
    Structure/object.h \
    Structure/layer.h \
    Structure/editor.h \
    Interface/dialogwindows.h \
    Interface/dockwidgets.h \
    Structure/brush.h \
    Overloads.h \
    Interface/odessa_ui.h \
    Structure/primitive.h \
    Structure/gleditor.h \
    Interface/panels.h \
    Interface/slideedit.h \
    Structure/Canvas/canvas.h \
    Interface/colorwheel.h


RESOURCES += \
    icons.qrc
