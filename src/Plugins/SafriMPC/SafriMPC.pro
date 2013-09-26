#-------------------------------------------------
#
# Project created by QtCreator 2013-09-13T11:57:32
#
#-------------------------------------------------

QT       += network gui widgets



TARGET = SafriMPC
TEMPLATE = lib

DEFINES += SAFRIMPC_LIBRARY

SOURCES += SafriMPCPlugin.cpp \
    MPCInserter.cpp

HEADERS += SafriMPCPlugin.h\
        safrimpc_global.h \
    MPCInserter.h


PROVIDER = safri
include(../../SafriPlugin.pri)
INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore



OTHER_FILES += \
    SafriMPC.xml \
    safrimpc.json
