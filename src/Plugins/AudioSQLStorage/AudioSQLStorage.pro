#-------------------------------------------------
#
# Project created by QtCreator 2013-04-11T00:25:21
#
#-------------------------------------------------

QT       += sql

QT       -= gui

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

TARGET = AudioSQLStorage
TEMPLATE = lib

DEFINES += AUDIOSQLSTORAGE_LIBRARY

SOURCES += audiosqlstorageplugin.cpp \
    audiosqlstorage.cpp \
    audiosqlstoragefactory.cpp \
    isqlstorage.cpp \
    sqlitestorage.cpp

HEADERS += audiosqlstorageplugin.h\
        AudioSQLStorage_global.h \
    audiosqlstorage.h \
    audiosqlstoragefactory.h \
    isqlstorage.h \
    sqlitestorage.h \
    SQLStatements.h

OTHER_FILES += \
    audiosqlstorageplugin.json \
				AudioSQLStorage.xml
