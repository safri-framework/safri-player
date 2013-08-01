#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T01:57:31
#
#-------------------------------------------------

QT       -= gui

TARGET = DarkBlueSkin
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

# Link against the MainWindow plugin for the skin interface
INCLUDEPATH += ../MainWindow
LIBS += -L"../../../bin/plugins/safri" -lMainWindow

DEFINES += DARKBLUESKIN_LIBRARY

SOURCES += DarkBlueSkinPlugin.cpp

HEADERS += DarkBlueSkinPlugin.h\
        darkblueskin_global.h

OTHER_FILES += \
    DarkBlueSkin.xml \
    DarkBlueSkin.json \
    stylesheet.css \
    darkblueskin.json

RESOURCES += \
    ressources.qrc
