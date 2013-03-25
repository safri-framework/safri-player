#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T16:34:44
#
#-------------------------------------------------

TARGET = SafriMobileGuiQML
TEMPLATE = lib

QT += quick widgets

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

OTHER_FILES += \
    safrimobileguiqml.json \
    qml/PlayerButton.qml \
    qml/Player.qml \
    qml/MusicSelection.qml \
    qml/main.qml \
    qml/Home.qml \
    qml/functions.js \
    qml/Footer.qml \
    qml/TreeView.qml

