QT       += gui widgets
QT       += xml

TARGET = PluginSystem
TEMPLATE = lib

include(../Defines.pri)

CONFIG += thread console

DEFINES += PLUGINSYSTEM_LIBRARY
DESTDIR = ../../lib

#DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += \
        iplugin.cpp \
        pluginmanager.cpp \
        pluginspec.cpp \
    plugindependency.cpp \
    pluginviewer.cpp \
    pluginviewermodel.cpp \
    pluginspecviewer.cpp

HEADERS +=\
        PluginSystem_global.h \
        iplugin.h \
        pluginmanager.h \
        pluginspec.h \
    plugindependency.h \
    pluginviewer.h \
    pluginviewermodel.h \
    pluginspecviewer.h

FORMS += \
    pluginviewer.ui \
    pluginspecviewer.ui

INCLUDEPATH += -L/usr/include/i386-linux-gnu/c++/4.7/
