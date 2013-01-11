#-------------------------------------------------
#
# Project created by QtCreator 2012-12-20T22:18:34
#
#-------------------------------------------------

TARGET = SongtreeWidget
TEMPLATE = lib

PROVIDER = safri
include(../../SafriPlugin.pri)

INCLUDEPATH += ../CorePlugin
LIBS += -L"../../../bin/plugins/safri" -lCore

DEFINES += SONGTREEWIDGET_LIBRARY

SOURCES += \
    SongtreeWidgetPlugin.cpp \
    SongtreeWidget.cpp \
    songtreesidebarwrapper.cpp

HEADERS +=\
        SongtreeWidget_global.h \
    SongtreeWidgetPlugin.h \
    SongtreeWidget.h \
    songtreesidebarwrapper.h

FORMS += \
    SongtreeWidget.ui

OTHER_FILES += \
    SongTreeWidget.xml

