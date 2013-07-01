#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T16:34:44
#
#-------------------------------------------------

TARGET = SafriApp
TEMPLATE = lib

QT += quick widgets

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += SAFRIMOBILEGUIQML_LIBRARY

SOURCES += \
    SafriAppPlugin.cpp \
    SafriAppInstance.cpp

HEADERS +=\
    SafriAppInstance.h \
    SafriAppPlugin.h \
    SafriApp_global.h

RESOURCES += \
    QMLResources.qrc

OTHER_FILES += \
    qml/PlayerButton.qml \
    qml/Player.qml \
    qml/MusicSelection.qml \
    qml/main.qml \
    qml/Home.qml \
    qml/functions.js \
    qml/Footer.qml \
    qml/TreeView.qml \
    safriapp.json \
    SafriApp.xml \
    qml/View1.qml \
    qml/TreeView.qml \
    qml/View2.qml \
    qml/Dialer.qml \
    qml/RotaryDialer.js \
    qml/MusicProgress.qml \
    MarqueeText.qml \
    qml/MarqueeText.qml

