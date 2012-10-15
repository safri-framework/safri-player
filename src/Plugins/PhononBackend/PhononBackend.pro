#-------------------------------------------------
#
# Project created by QtCreator 2012-10-15T22:08:23
#
#-------------------------------------------------

QT       += phonon

QT       -= gui

TARGET = PhononBackend
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += PHONONBACKEND_LIBRARY

SOURCES += phononbackendplugin.cpp \
    phononbackend.cpp

HEADERS += phononbackendplugin.h\
        PhononBackend_global.h \
    phononbackend.h
