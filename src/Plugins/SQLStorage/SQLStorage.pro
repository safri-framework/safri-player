#-------------------------------------------------
#
# Project created by QtCreator 2012-11-23T22:55:48
#
#-------------------------------------------------

QT       += sql widgets

#QT       -= gui

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

TARGET = SQLStorage
TEMPLATE = lib

DEFINES += SQLSTORAGE_LIBRARY

SOURCES += sqlstorageplugin.cpp \
    sqlstorageadapter.cpp \
    audiosqlstoragefactory.cpp \
    audiosqlstorageadapter.cpp

HEADERS += sqlstorageplugin.h\
        SQLStorage_global.h \
    sqlstorageadapter.h \
    audiosqlstoragefactory.h \
    audiosqlstorageadapter.h

OTHER_FILES += \
    SQLStorage.xml \
    sqlstorageplugin.json
