#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T02:46:23
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = gestureDetectorApp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    abstractframeproducer.cpp

HEADERS += \
    abstractframeproducer.h

OTHER_FILES += \
    libs.pri

include(libs.pri)
