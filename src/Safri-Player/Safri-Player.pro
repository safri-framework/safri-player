#-------------------------------------------------
#
# Project created by QtCreator 2012-09-18T16:26:59
#
#-------------------------------------------------

SAFRI_VERSION = 0.3.1

QT       += core gui

TARGET = Safri-Player
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = ../../bin

INCLUDEPATH += ../PluginSystem
LIBS += -lPluginSystem -L../../lib

VERSTR = '\\"$${SAFRI_VERSION}\\"'
DEFINES += SAFRI_VERSION=\"$${VERSTR}\"

SOURCES += main.cpp
