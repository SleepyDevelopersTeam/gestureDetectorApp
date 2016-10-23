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
    abstractframeproducer.cpp \
    webcameraframeproducer.cpp \
    abstractgda.cpp \
    abstractgesturedescriptor.cpp \
    gesturelibrary.cpp \
    historgamshadowdescriptor.cpp \
    historgamgesturedescriptor.cpp

HEADERS += \
    abstractframeproducer.h \
    webcameraframeproducer.h \
    abstractgda.h \
    abstractgesturedescriptor.h \
    gesturelibrary.h \
    historgamshadowdescriptor.h \
    historgamgesturedescriptor.h

include(libs.pri)
