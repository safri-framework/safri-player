#-------------------------------------------------
#
# Project created by QtCreator 2013-06-17T17:58:43
#
#-------------------------------------------------

QT       += widgets xml

TARGET = TabbedPlaylistWidget
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += TABBEDPLAYLISTWIDGET_LIBRARY

SOURCES += TabbedPlaylistWidgetPlugin.cpp \
    TabbedPlaylistWidget.cpp \
    TabbedPLWidgetFactory.cpp \
    PlaylistView.cpp \
    PlaylistModel.cpp \
    PlaylistTabWidget.cpp \
    playlistitemdelegate.cpp \
    PlaylistTabBar.cpp \
    TabbedPlaylistSettingsWidget.cpp

HEADERS += TabbedPlaylistWidgetPlugin.h\
        tabbedplaylistwidget_global.h \
    TabbedPlaylistWidget.h \
    TabbedPLWidgetFactory.h \
    PlaylistView.h \
    PlaylistModel.h \
    PlaylistTabWidget.h \
    playlistitemdelegate.h \
    PlaylistTabBar.h \
    TabbedPlaylistSettingsWidget.h

OTHER_FILES += \
    TabbedPlaylistWidget.xml \
    TabbedPlaylistWidget.json

FORMS += \
    TabbedPlaylistWidget.ui \
    TabbedPlaylistSettingsWidget.ui

RESOURCES += \
    ressources.qrc
