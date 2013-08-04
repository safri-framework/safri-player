#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T20:57:08
#
#-------------------------------------------------

QT       += widgets

TARGET = DarkBluePlayerWidget
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += DARKBLUEPLAYERWIDGET_LIBRARY

SOURCES += DarkBluePlayerWidgetPlugin.cpp \
    DarkBluePlayerWidget.cpp \
    PlayerWidgetFactory.cpp \
    PlayerControl.cpp

HEADERS += DarkBluePlayerWidgetPlugin.h\
        darkblueplayerwidget_global.h \
    DarkBluePlayerWidget.h \
    PlayerWidgetFactory.h \
    PlayerControl.h

OTHER_FILES += \
    darkblueplayerwidget.json \
    DarkBluePlayerWidget.xml \
    DarkBluePlayerStylesheet.css

FORMS += \
    DarkBluePlayerWidget.ui

RESOURCES += \
    ressources.qrc
