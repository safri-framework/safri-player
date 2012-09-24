#-------------------------------------------------
#
# Project created by QtCreator 2012-09-24T20:21:28
#
#-------------------------------------------------

QT       -= gui

TARGET = Core
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

DEFINES += COREPLUGIN_LIBRARY

SOURCES += coreplugin.cpp

HEADERS += coreplugin.h\
        CorePlugin_global.h

OTHER_FILES += \
    Core.xml
