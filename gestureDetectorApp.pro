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
    histogram/foneaccumulator.cpp \
    histogram/accumulator.cpp \
    histogram/gesturedetector.cpp \
    gda/histogramgda.cpp \
    common/utils/normalizearray.cpp \
    gl/abstractgesturelistener.cpp

HEADERS += \
    frameproducers/abstractframeproducer.h \
    frameproducers/webcameraframeproducer.h \
    gda/abstractgda.h \
    descriptors/abstractgesturedescriptor.h \
    descriptors/historgamgesturedescriptor.h \
    common/gesturelibrary.h \
    histogram/historgamshadowdescriptor.h \
    histogram/foneaccumulator.h \
    histogram/accumulator.h \
    histogram/gesturedetector.h \
    gda/histogramgda.h \
    gl/abstractgesturelistener.h


include(libs.pri)
