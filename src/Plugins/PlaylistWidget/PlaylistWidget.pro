#-------------------------------------------------
#
# Project created by QtCreator 2012-12-17T17:10:51
#
#-------------------------------------------------

TARGET = PlaylistWidget
TEMPLATE = lib

QT += widgets

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += PLAYLISTWIDGET_LIBRARY

SOURCES += playlistwidgetplugin.cpp \
    playlistwidget.cpp \
    playlistwidgetfactory.cpp \
    playlistmodel.cpp \
    playlistitemdelegate.cpp \
    playlistview.cpp

HEADERS += playlistwidgetplugin.h\
        PlaylistWidget_global.h \
    playlistwidget.h \
    playlistwidgetfactory.h \
    playlistmodel.h \
    playlistitemdelegate.h \
    playlistview.h

FORMS += \
    playlistwidget.ui

OTHER_FILES += \
    PlaylistWidget.xml \
    playlistwidget.json

RESOURCES += \
    ressources.qrc
