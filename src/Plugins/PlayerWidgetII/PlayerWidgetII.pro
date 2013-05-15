#-------------------------------------------------
#
# Project created by QtCreator 2013-01-15T20:40:03
#
#-------------------------------------------------

TARGET = PlayerWidgetII
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore


DEFINES += PLAYERWIDGETII_LIBRARY

SOURCES += \
    widget.cpp \
    plwidgetfactory.cpp \
    playerwidgetII_plugin.cpp \
    PlayerSettingsDialog.cpp

HEADERS +=\
        PlayerWidgetII_global.h \
    widget.h \
    plwidgetfactory.h \
    playerwidgetII_plugin.h \
    PlayerSettingsDialog.h

OTHER_FILES += \
    styles.css \
    playerwidgetII.json

FORMS += \
    widget.ui \
    PlayerSettingsDialog.ui

RESOURCES += \
    ressources.qrc \
    ressources.qrc

QT += widgets
