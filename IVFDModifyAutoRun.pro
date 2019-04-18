QT += core
QT -= gui

TARGET = IVFDModifyAutoRun
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    IVFDDriver.cpp \
    MainModule.cpp

HEADERS += \
    IVFDDriver.h \
    MainModule.h

