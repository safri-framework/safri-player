QT       += gui
QT       += xml

TARGET = PluginSystem
TEMPLATE = lib

CONFIG += thread

DEFINES += PLUGINSYSTEM_LIBRARY
DESTDIR = ../../lib

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

