#-------------------------------------------------
#
# Project created by QtCreator 2013-05-24T01:02:36
#
#-------------------------------------------------

QT       -= gui

TARGET = AlbumCovers
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += ALBUMCOVERS_LIBRARY

SOURCES += AlbumCoversPlugin.cpp \
    CoverAssetService.cpp

HEADERS += AlbumCoversPlugin.h\
        albumcovers_global.h \
    CoverAssetService.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    albumcovers.json \
    AlbumCovers.xml
