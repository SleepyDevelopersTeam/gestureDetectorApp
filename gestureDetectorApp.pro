#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T02:46:23
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

QMAKE_CXXFLAGS += -std=gnu++0x

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
    gl/abstractgesturelistener.cpp \
    frameproducers/lncframeproducer.cpp \
    common/utils/displayframeconsumer.cpp \
    gl/consoleloggesturelistener.cpp \
    gl/appclosegesturelistener.cpp \
    common/backgrounddetector.cpp \
    histogram/histogram.cpp \
    histogram/shadowpreproducer.cpp \
    histogram/histogramdrawer.cpp

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
    gl/abstractgesturelistener.h \
    frameproducers/lncframeproducer.h \
    common/utils/displayframeconsumer.h \
    gl/consoleloggesturelistener.h \
    gl/appclosegesturelistener.h \
    common/backgrounddetector.h \
    histogram/histogram.h \
    histogram/shadowpreproducer.h \
    histogram/histogramdrawer.h


include(libs.pri)
