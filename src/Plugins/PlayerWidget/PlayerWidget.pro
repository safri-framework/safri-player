#-------------------------------------------------
#
# Project created by QtCreator 2012-12-10T16:23:38
#
#-------------------------------------------------

TARGET = PlayerWidget
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

QT += widgets

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += PLAYERWIDGET_LIBRARY

SOURCES += playerwidgetplugin.cpp \
    playerwidget.cpp \
    playerwidgetfactory.cpp

HEADERS += playerwidgetplugin.h\
    playerwidget.h \
    playerwidgetfactory.h \
    PlayerWidget_global.h

FORMS += \
    playerwidget.ui

OTHER_FILES += \
    PlayerWidget.xml \
    ressources/stylesheet.css \
    playerwidget.json

RESOURCES += \
    ressources.qrc
