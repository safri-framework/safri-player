#-------------------------------------------------
#
# Project created by QtCreator 2012-09-24T20:21:28
#
#-------------------------------------------------

QT       -= gui

TARGET = Core
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

DEFINES += COREPLUGIN_LIBRARY

SOURCES += coreplugin.cpp \
    CoreData/basedto.cpp \
    CoreData/genre.cpp \
    CoreData/artist.cpp \
    CoreData/album.cpp \
    CoreData/song.cpp \
    icore.cpp

HEADERS += coreplugin.h\
        CorePlugin_global.h \
    iplaybackcontroller.h \
    CoreData/basedto.h \
    CoreData/genre.h \
    CoreData/artist.h \
    CoreData/album.h \
    CoreData/song.h\
    iplaylist.h \
    icore.h

OTHER_FILES += \
    Core.xml
