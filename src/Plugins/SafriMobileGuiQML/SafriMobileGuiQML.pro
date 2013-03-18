#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T16:34:44
#
#-------------------------------------------------

TARGET = SafriMobileGuiQML
TEMPLATE = lib

QT += declarative

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += SAFRIMOBILEGUIQML_LIBRARY

SOURCES += safrimobileguiqml.cpp \
    safrimobileguiinstance.cpp

HEADERS += safrimobileguiqml.h\
        SafriMobileGuiQML_global.h \
    safrimobileguiinstance.h

RESOURCES += \
    QMLResources.qrc

