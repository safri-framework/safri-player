#-------------------------------------------------
#
# Project created by QtCreator 2012-10-02T16:00:36
#
#-------------------------------------------------

QT       -= gui

TARGET = PlaybackController
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += PLAYBACKCONTROLLER_LIBRARY

SOURCES += playbackcontroller.cpp \
    playbackcontrollerplugin.cpp

HEADERS += playbackcontroller.h\
        PlaybackController_global.h \
    playbackcontrollerplugin.h
