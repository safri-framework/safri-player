#-------------------------------------------------
#
# Project created by QtCreator 2012-10-15T23:18:30
#
#-------------------------------------------------

TARGET = HackingWidget
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += HACKINGWIDGET_LIBRARY

SOURCES += hackingwidgetplugin.cpp \
    hackingwidget.cpp

HEADERS += hackingwidgetplugin.h\
        HackingWidget_global.h \
    hackingwidget.h

FORMS += \
    hackingwidget.ui
