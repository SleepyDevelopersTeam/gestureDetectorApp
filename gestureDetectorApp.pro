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
    frameproducers/abstractframeproducer.cpp \
    frameproducers/webcameraframeproducer.cpp \
    gda/abstractgda.cpp \
    descriptors/abstractgesturedescriptor.cpp \
    descriptors/historgamgesturedescriptor.cpp \
    common/gesturelibrary.cpp \
    histogram/historgamshadowdescriptor.cpp \
    gda/histogramgda.cpp \
    common/utils/normalizearray.cpp

HEADERS += \
    frameproducers/abstractframeproducer.h \
    frameproducers/webcameraframeproducer.h \
    gda/abstractgda.h \
    descriptors/abstractgesturedescriptor.h \
    descriptors/historgamgesturedescriptor.h \
    common/gesturelibrary.h \
    historgam/historgamshadowdescriptor.h \
    gda/histogramgda.h


include(libs.pri)
