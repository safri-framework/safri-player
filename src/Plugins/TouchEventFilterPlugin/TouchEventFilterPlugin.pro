#-------------------------------------------------
#
# Project created by QtCreator 2013-04-21T22:31:05
#
#-------------------------------------------------

QT       -= gui
QT       += widgets

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

TARGET = TouchEventFilterPlugin
TEMPLATE = lib

DEFINES += TOUCHEVENTFILTERPLUGIN_LIBRARY

SOURCES += toucheventfilterplugin.cpp \
    toucheventfilter.cpp

HEADERS += toucheventfilterplugin.h\
        TouchEventFilterPlugin_global.h \
    toucheventfilter.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    toucheventfilterplugin.json
