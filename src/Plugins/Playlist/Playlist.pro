#-------------------------------------------------
#
# Project created by QtCreator 2012-10-02T16:37:05
#
#-------------------------------------------------

QT       -= gui

TARGET = Playlist
TEMPLATE = lib

DEFINES += PLAYLIST_LIBRARY

SOURCES += playlistplugin.cpp \
    playlist.cpp

HEADERS += playlistplugin.h\
        Playlist_global.h \
    playlist.h

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

OTHER_FILES += \
    Playlist.xml
