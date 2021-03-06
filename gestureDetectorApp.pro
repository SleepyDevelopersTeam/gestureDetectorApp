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
	descriptors/gesture/abstractgesturedescriptor.cpp \
	common/gesturelibrary.cpp \
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
	histogram/histogramdrawer.cpp \
	descriptors/pose/abstractposedescriptor.cpp \
    descriptors/pose/histogramposedescriptor.cpp \
    descriptors/gesture/keyposegesturedescriptor.cpp \
    common/utils/descriptorwriter.cpp \
    descriptors/pose/allinoneposedescriptor.cpp \
    neuro/neuroclassifier.cpp \
    gda/neurogda.cpp \
    descriptors/gesture/neurokpgdescriptor.cpp \
    gda/neurobsgda.cpp

HEADERS += \
	frameproducers/abstractframeproducer.h \
	frameproducers/webcameraframeproducer.h \
	gda/abstractgda.h \
	descriptors/gesture/abstractgesturedescriptor.h \
	common/gesturelibrary.h \
	gda/histogramgda.h \
	gl/abstractgesturelistener.h \
	frameproducers/lncframeproducer.h \
	common/utils/displayframeconsumer.h \
	gl/consoleloggesturelistener.h \
	gl/appclosegesturelistener.h \
	common/backgrounddetector.h \
	histogram/histogram.h \
	histogram/shadowpreproducer.h \
	histogram/histogramdrawer.h \
	descriptors/pose/abstractposedescriptor.h \
    descriptors/pose/histogramposedescriptor.h \
    descriptors/gesture/keyposegesturedescriptor.h \
    common/utils/descriptorwriter.h \
    descriptors/pose/allinoneposedescriptor.h \
    neuro/neuroclassifier.h \
    gda/neurogda.h \
    descriptors/gesture/neurokpgdescriptor.h \
    gda/neurobsgda.h


include(libs.pri)
