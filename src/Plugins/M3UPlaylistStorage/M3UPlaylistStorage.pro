#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T22:05:44
#
#-------------------------------------------------

QT       -= gui

TARGET = M3UPlaylistStorage
TEMPLATE = lib

PROVIDER = safri

include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore


DEFINES += M3UPLAYLISTSTORAGE_LIBRARY

SOURCES += M3UPlaylistStoragePlugin.cpp \
    M3UPlaylistStorage.cpp

HEADERS += M3UPlaylistStoragePlugin.h \
    M3UPlaylistStorage_global.h \
    M3UPlaylistStorage.h

OTHER_FILES += \
    M3UPlaylistStorage.json \
    M3UPlaylistStorage.xml
