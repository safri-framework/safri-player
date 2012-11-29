#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T15:38:01
#
#-------------------------------------------------

QT       -= gui

TARGET = AudioCollection
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += AUDIOCOLLECTION_LIBRARY

SOURCES += audiocollectionplugin.cpp \
    audiocollection.cpp \
    audiocollectionbuilder.cpp

HEADERS += audiocollectionplugin.h\
        AudioCollection_global.h \
    audiocollection.h \
    audiocollectionbuilder.h

OTHER_FILES += \
    AudioCollection.xml

