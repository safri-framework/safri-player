QT       -= gui
QT       += xml

TARGET = PluginSystem
TEMPLATE = lib

DEFINES += PLUGINSYSTEM_LIBRARY
DESTDIR = ../../lib

SOURCES += \
        iplugin.cpp \
        pluginmanager.cpp \
        pluginspec.cpp \
    plugindependency.cpp

HEADERS +=\
        PluginSystem_global.h \
        iplugin.h \
        pluginmanager.h \
        pluginspec.h \
    plugindependency.h

