#-------------------------------------------------
#
# Project created by QtCreator 2013-04-25T20:44:01
#
#-------------------------------------------------

#QT       -= gui
QT       += network xml gui

PROVIDER = safri

include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

TARGET = LastFMInfoResolver
TEMPLATE = lib

DEFINES += LASTFMINFORESOLVER_LIBRARY

SOURCES += LastFMInfoResolver.cpp \
    LastFMINfoResolverPlugin.cpp

HEADERS += LastFMInfoResolver.h\
        lastfminforesolver_global.h \
    LastFMINfoResolverPlugin.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    lastfminforesolverplugin.json \
    LastFMInfoResolver.xml
