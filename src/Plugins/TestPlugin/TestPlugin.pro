#-------------------------------------------------
#
# Project created by QtCreator 2012-09-18T16:20:19
#
#-------------------------------------------------

QT       += gui

TARGET = TestPlugin
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

DEFINES += TESTPLUGIN_LIBRARY

SOURCES += testplugin.cpp

HEADERS += testplugin.h\
        TestPlugin_global.h

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

OTHER_FILES += \
    testplugin.xml \
    testplugin.json
