#-------------------------------------------------
#
# Project created by QtCreator 2012-12-13T18:14:04
#
#-------------------------------------------------

TARGET = SidebarPluginTest
TEMPLATE = lib

DEFINES += SIDEBARPLUGINTEST_LIBRARY

SOURCES += sidebarplugintest.cpp \
    sidebarplugintestplugin.cpp

HEADERS += sidebarplugintest.h\
        SidebarPluginTest_global.h \
    sidebarplugintestplugin.h

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore
